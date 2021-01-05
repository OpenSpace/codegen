#include <array>
#include <cassert>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
#include <map>
#include <optional>
#include <string_view>
#include <unordered_map>

#ifdef WIN32
#pragma warning (disable : 4996)
#endif // WIN32

//#define PRINT_MEMORY_USAGE

namespace {
    constexpr const char AttributeDictionary[] = "[[codegen::Dictionary";
    constexpr const int ErrorContext = 50;

    template <typename... Ts>
    [[noreturn]] void Fail(const char buf[], Ts... params) {
        printf(buf, params...);
        exit(EXIT_FAILURE);
    }
} // namespace

struct State {
    std::string_view line;
    std::string commentBuffer;
    std::vector<std::string_view> structs;

    std::map<std::string, std::string, std::less<>> structComments;
    std::pair<std::string, std::string> rootStruct;

    char* resultVerifierBase = nullptr;
    char* resultVerifier = nullptr;

    std::map<std::string, std::string, std::less<>> structConverters;
    char* resultConverterBase = nullptr;
    char* resultConverter = nullptr;

    char* scratchSpace = nullptr;
};

struct Struct {
    std::string_view name;

    std::string_view attributeRenderable;
};

struct Variable {
    std::string_view type;
    std::string_view name;

    std::string_view attributeKey;
    std::string_view attributeInRange;
};

//
// Helper functions
//
std::string_view strip(std::string_view sv) {
    const size_t strBegin = sv.find_first_not_of(' ');
    if (strBegin == std::string::npos) {
        return sv;
    }

    const size_t strEnd = sv.find_last_not_of(' ');
    const size_t strRange = strEnd - strBegin + 1;
    return sv.substr(strBegin, strRange);
}

bool startsWith(std::string_view lhs, std::string_view rhs) {
    return lhs.size() >= rhs.size() && lhs.substr(0, rhs.size()) == rhs;
}

std::string join(const std::vector<std::string_view>& list, std::string sep) {
    size_t size = 0;
    for (std::string_view l : list) {
        size += l.size();
    }
    // this allocates space for one sep more than needed, but it simplifies the for loop
    size += sep.size() * list.size();

    std::string res;
    res.reserve(size + 1);
    for (std::string_view l : list) {
        res.append(l.data(), l.size());
        res.append(sep);
    }
    return res.substr(0, res.size() - sep.size());
}

std::string_view extractLine(std::string_view sv, size_t* cursor) {
    assert(cursor);
    assert(*cursor == 0 || sv[*cursor - 1] == '\n');
    const size_t p = sv.find('\n', *cursor);

    if (p != std::string_view::npos) {
        std::string_view line = sv.substr(*cursor, p - *cursor);
        *cursor = p + 1;
        return strip(line);
    }
    else {
        std::string_view line = sv.substr(*cursor);
        *cursor = std::string_view::npos;
        return strip(line);
    }
}

void handleCommentLine(State& state) {
    std::string_view comment = strip(state.line.substr(2));
    state.commentBuffer.append(comment);
}

std::string_view parseAttribute(std::string_view block, std::string_view name) {
    std::string key = std::string("codegen::" + std::string(name));
    const size_t p = block.find(key);
    if (p == std::string_view::npos) {
        return std::string_view();
    }
    const size_t beg = block.find('(', p) + 1;
    const size_t end = block.find(')', beg);

    std::string_view content = block.substr(beg, end - beg);
    return content;
}

Struct parseStruct(std::string_view line) {
    Struct s;

    size_t cursor = line.find(' ');
    assert(line.substr(0, cursor) == "struct");
    cursor++;

    const size_t beginAttribute = line.find("[[", cursor);
    if (beginAttribute != std::string_view::npos) {
        const size_t endAttribute = line.find("]]", beginAttribute) + 2;
        if (endAttribute == std::string_view::npos) {
            Fail(
                "Could not find closing bracket for attribute in struct:\n%s",
                std::string(line).c_str()
            );
        }

        size_t beginName = line.find('(', beginAttribute);
        if (beginName == std::string_view::npos) {
            Fail("No name specified for root struct:\n%s", std::string(line).c_str());
        }

        beginName++;
        const size_t endName = line.find(')', beginName);
        if (beginName == endName) {
            Fail("No name specified for root struct:\n%s", std::string(line).c_str());
        }

        s.attributeRenderable = line.substr(beginName, endName - beginName);
        cursor = endAttribute + 1;
    }

    const size_t endStruct = line.find(' ', cursor);
    if (endStruct == std::string_view::npos) {
        Fail(
            "Missing space before the closing { of a struct:\n%s",
            std::string(line).c_str()
        );
    }
    s.name = line.substr(cursor, endStruct - cursor);
    return s;
}

Variable parseVariable(std::string_view line) {
    if (line.back() != ';') {
        Fail(
            "Variable definitions over multiple lines not supported:\n%s",
            std::string(line).c_str()
        );
    }
    // Remove the trailing ;
    line.remove_suffix(1);

    const size_t p1 = line.find(' ');
    const size_t p2 = line.find(' ', p1 + 1);
    if (p1 == std::string_view::npos) {
        Fail("Too few spaces in variable definition:\n%s", std::string(line).c_str());
    }

    Variable res;
    res.type = line.substr(0, p1);
    res.name = line.substr(p1 + 1, p2 - p1 - 1);
    if (p2 != std::string_view::npos) {
        std::string_view attributes = line.substr(p2 + 1);
        res.attributeInRange = parseAttribute(attributes, "inrange");
        res.attributeKey = parseAttribute(attributes, "key");
    }

    return res;
}

std::string resolveComment(std::string comment) {
    if (size_t it = comment.find("codegen::description"); it != std::string::npos) {
        const size_t l = std::string_view("codegen::description").size();
        it += l;
        if (comment[it] != '(') {
            Fail(
                "Malformed codegen::description. Expected ( after token:\n%s",
                comment.c_str()
            );
        }
        it++;
        size_t end = comment.find(')', it);
        std::string identifier = comment.substr(it, end - it);
        comment = identifier + ".description";
    }
    else {
        comment = std::string("\"") + comment + "\"";
    }
    return comment;
}

std::string verifier(std::string_view type, State& state) {
    static std::unordered_map<std::string_view, std::string_view> VerifierMapping = {
        { "bool", "BoolVerifier" },
        { "int", "IntVerifier" },
        { "double", "DoubleVerifier" },
        { "std::string", "StringVerifier" },
        { "glm::ivec2", "IntVector2Verifier" },
        { "glm::ivec3", "IntVector3Verifier" },
        { "glm::ivec4", "IntVector4Verifier" },
        { "glm::dvec2", "DoubleVector2Verifier" },
        { "glm::dvec3", "DoubleVector3Verifier" },
        { "glm::dvec4", "DoubleVector4Verifier" },
        { "glm::dmat2x2", "DoubleMatrix2x2Verifier" },
        { "glm::dmat2x3", "DoubleMatrix2x3Verifier" },
        { "glm::dmat2x4", "DoubleMatrix2x4Verifier" },
        { "glm::dmat3x2", "DoubleMatrix3x2Verifier" },
        { "glm::dmat3x3", "DoubleMatrix3x3Verifier" },
        { "glm::dmat3x4", "DoubleMatrix3x4Verifier" },
        { "glm::dmat4x2", "DoubleMatrix4x2Verifier" },
        { "glm::dmat4x3", "DoubleMatrix4x3Verifier" },
        { "glm::dmat4x4", "DoubleMatrix4x4Verifier" }
    };

    if (auto it = VerifierMapping.find(type); it != VerifierMapping.end()) {
        return std::string("new ") + std::string(it->second);
    }
    else if (startsWith(type, "std::vector<")) {
        std::string_view subtype = type.substr(12);
        subtype.remove_suffix(1);

        std::string comments;
        if (auto it = state.structComments.find(subtype); it != state.structComments.end()) {
            comments = resolveComment(it->second);
        }

        std::string ver = verifier(subtype, state);
        std::array<char, 256> Buf;
        std::fill(Buf.begin(), Buf.end(), '\0');
        int n = sprintf(
            Buf.data(),
            "new TableVerifier({{\"*\",%s,Optional::Yes, %s}})",
            ver.c_str(),
            comments.c_str()
        );
        return std::string(Buf.data(), Buf.data() + n);
    }
    else {
        return std::string("codegen_") + join(state.structs, "_") + "_" + std::string(type);
    }
}

void handleStructStart(State& state) {
    // Verifier
    {
        std::string name = "codegen_" + join(state.structs, "_");
        int n = sprintf(
            state.resultVerifier,
            "TableVerifier* %s=new TableVerifier;", name.c_str()
        );
        state.resultVerifier += n;
    }
}

void handleStructEnd(State& state) {
    std::string name = join(state.structs, "::");
    int n = sprintf(
        state.resultConverter,
        "template<> void bakeTo<%s>(const ghoul::Dictionary& d, std::string_view key, %s* val) {"
        "%s res;",
        name.c_str(),
        name.c_str(),
        name.c_str()
    );
    state.resultConverter += n;


    auto it = state.structConverters.find(name);
    if (it == state.structConverters.end()) {
        Fail("Empty structs are not allowed:\n%s", name.c_str());
    }

    std::memcpy(state.resultConverter, it->second.data(), it->second.size());
    state.resultConverter += it->second.size();

    n = sprintf(
        state.resultConverter,
        "*val = res;}"
    );
    state.resultConverter += n;
}

void handleVariable(Variable var, State& state) {
    std::string ver = std::string("codegen_") + join(state.structs, "_");
    std::string variableName;

    if (var.attributeKey.empty()) {
        variableName = std::string(var.name);
        variableName[0] = static_cast<char>(::toupper(variableName[0]));
    }
    else {
        variableName = std::string(var.attributeKey);
    }

    state.commentBuffer = resolveComment(state.commentBuffer);

    bool isOptional = false;
    if (startsWith(var.type, "std::optional<")) {
        isOptional = true;
        var.type.remove_prefix(std::string_view("std::optional<").size());
        var.type.remove_suffix(1);
    }

    std::string v = verifier(var.type, state);
    int n = sprintf(
        state.resultVerifier,
        "%s->documentations.push_back({\"%s\",%s,%s,%s});",
        ver.c_str(), variableName.c_str(), v.c_str(),
        isOptional ? "Optional::Yes" : "Optional::No", state.commentBuffer.c_str()
    );
    state.resultVerifier += n;
    state.commentBuffer.clear();


    // Converter
    std::string converter;
    std::string name = join(state.structs, "::");
    if (auto it = state.structConverters.find(name); it != state.structConverters.end()) {
        converter = it->second;
    }

    //std::vector<std::string_view> structs = state.structs;
    //structs.pop_back();
    //structs.push_back(var.type);
    //std::string fqType = join(structs, "::");



    n = sprintf(
        state.scratchSpace,
        "bakeTo(d, \"%s\", &res.%s);",
        //std::string(var.type).c_str(),
        variableName.c_str(),
        std::string(var.name).c_str()
    );
    
    converter += std::string(state.scratchSpace, state.scratchSpace + n);
    state.scratchSpace += n;
    state.structConverters[name] = converter;
}

std::string finalizeVerifier(State& state) {
    std::array<char, 512> Buf;
    std::fill(Buf.begin(), Buf.end(), '\0');
    int n = sprintf(
        Buf.data(),
        "namespace codegen { template<typename T>documentation::Documentation doc();"
        "template<>documentation::Documentation doc<%s>(){"
        "using namespace documentation;",
        state.rootStruct.second.c_str()
    );

    std::memmove(
        state.resultVerifierBase + n,
        state.resultVerifierBase,
        state.resultVerifier - state.resultVerifierBase
    );
    std::memcpy(state.resultVerifierBase, Buf.data(), n);
    state.resultVerifier += n;

    std::string rootStruct = std::string("codegen_") + state.rootStruct.first;
    n = sprintf(
        state.resultVerifier,
        "documentation::Documentation d;d.name=\"%s\";d.id=\"%s\";"
        "d.entries=std::move(%s->documentations);delete %s;return d;}}",
        state.rootStruct.second.c_str(),
        state.rootStruct.second.c_str(),
        rootStruct.c_str(),
        rootStruct.c_str()
    );
    state.resultVerifier += n;
    return std::string(state.resultVerifierBase, state.resultVerifier);
}

std::string finalizeConverter(State& state) {
    constexpr const char Preamble[] =
        "namespace codegen { using D = ghoul::Dictionary;"
        "template<typename T> void bakeTo(const D&, std::string_view, T*);"
        "template<> void bakeTo(const D& d, std::string_view key, bool* val) {"
            "*val = d.value<bool>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, int* val) {"
            "*val = static_cast<int>(d.value<double>(key));"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, double* val) {"
            "*val = d.value<double>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, std::string* val) {"
            "*val = d.value<std::string>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::ivec2* val) {"
            "*val = d.value<glm::dvec2>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::ivec3* val) {"
            "*val = d.value<glm::dvec3>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::ivec4* val) {"
            "*val = d.value<glm::dvec4>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::dvec2* val) {"
            "*val = d.value<glm::dvec2>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::dvec3* val) {"
            "*val = d.value<glm::dvec3>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::dvec4* val) {"
            "*val = d.value<glm::dvec4>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::dmat2x2* val) {"
            "*val = d.value<glm::dmat2x2>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::dmat2x3* val) {"
            "*val = d.value<glm::dmat2x3>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::dmat2x4* val) {"
            "*val = d.value<glm::dmat2x4>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::dmat3x2* val) {"
            "*val = d.value<glm::dmat3x2>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::dmat3x3* val) {"
            "*val = d.value<glm::dmat3x3>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::dmat3x4* val) {"
            "*val = d.value<glm::dmat3x4>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::dmat4x2* val) {"
            "*val = d.value<glm::dmat4x2>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::dmat4x3* val) {"
            "*val = d.value<glm::dmat4x3>(key);"
        "}"
        "template<> void bakeTo(const D& d, std::string_view key, glm::dmat4x4* val) {"
            "*val = d.value<glm::dmat4x4>(key);"
        "}"
        "template<typename T> void bakeTo("
            "const D& d, std::string_view key, std::optional<T>* val) {"
        "if (d.hasKey(key)) *val = d.value<T>(key); else *val = std::nullopt;}";

    //specialization for optional and vector
    
    // preamble contains \0 at the end
    std::memmove(
        state.resultConverterBase + sizeof(Preamble) - 1,
        state.resultConverterBase,
        state.resultConverter - state.resultConverterBase
    );
    std::memcpy(state.resultConverterBase, Preamble, sizeof(Preamble) - 1);
    state.resultConverter += sizeof(Preamble) - 1;

    std::string s(state.resultConverterBase, state.resultConverter);

    int n = sprintf(
        state.resultConverter,
        "}"
    );
    state.resultConverter += n;
    return std::string(state.resultConverterBase, state.resultConverter);
}

std::string_view validCode(std::string_view code) {
    const size_t mainLocation = code.find(AttributeDictionary);
    if (mainLocation == std::string_view::npos) {
        // We did't find the attrbute
        return std::string_view();
    }

    if (code.find(AttributeDictionary, mainLocation + 1) != std::string_view::npos) {
        Fail("We currently only support one struct per file annotated with %s, "
            "including commented out ones", AttributeDictionary
        );
    }

    const size_t lastNewLine = code.rfind('\n', mainLocation) + 1;
    size_t cursor = code.find('{', lastNewLine) + 1;
    
    for (int counter = 1; counter > 0; cursor++) {
        if (code[cursor] == '{') {
            counter++;
        }
        if (code[cursor] == '}') {
            counter--;
        }
    }

    return code.substr(lastNewLine, cursor - lastNewLine + 1);
}

void handleFile(std::string_view path) {
    if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path)) {
        Fail("Could not open file %s", std::string(path).c_str());
    }

    std::ifstream f(path);
    std::string str(std::istreambuf_iterator<char>{f}, {});
    std::string_view content = strip(validCode(str));
    if (content.empty()) {
        return;
    }

    State state;
    // The fivefold increase is a tunable parameter
    const size_t bufferSize = content.size() * 5;
    state.resultVerifierBase = new char[bufferSize];
    state.resultVerifier = state.resultVerifierBase;
    std::fill(state.resultVerifier, state.resultVerifier + bufferSize, '\0');

    state.resultConverterBase = new char[bufferSize];
    state.resultConverter = state.resultConverterBase;
    std::fill(state.resultConverter, state.resultConverter + bufferSize, '\0');

    char* scratchSpaceBase = new char[bufferSize];
    state.scratchSpace = scratchSpaceBase;
    std::fill(state.scratchSpace, state.scratchSpace + bufferSize, '\0');

    if (std::string_view s = content.substr(0, 6); s != "struct") {
        Fail(
            "[[codegen::Dictionary]] needs a 'struct' declaration immediately before on "
            "the same line. Found %s", std::string(s).c_str()
        );
    }

    if (size_t p = content.find("/*"); p != std::string_view::npos) {
        Fail(
            "Block comments are not allowed:\n%s",
            std::string(content.substr(p, ErrorContext)).c_str()
        );
    }

    size_t cursor = 0;
    while (cursor != std::string_view::npos) {
        state.line = extractLine(content, &cursor);
        if (state.line.empty()) {
            continue;
        }

        if (startsWith(state.line, "//")) {
            handleCommentLine(state);
            continue;
        }

        if (startsWith(state.line, "struct")) {
            Struct s = parseStruct(state.line);
            state.structs.push_back(s.name);
            state.structComments[std::string(s.name)] = state.commentBuffer;
            state.commentBuffer.clear();
            
            if (!s.attributeRenderable.empty()) {
                assert(state.rootStruct.first.empty() && state.rootStruct.second.empty());
                state.rootStruct.first = s.name;
                state.rootStruct.second = s.attributeRenderable;
            }

            handleStructStart(state);
            continue;
        }

        if (startsWith(state.line, "};")) {
            if (!state.commentBuffer.empty()) {
                Fail("Unaccounted for comments at the end of a struct definition");
            }

            handleStructEnd(state);
            state.structs.pop_back();
            continue;
        }

        // If we got this far, we must be in a variable definition
        Variable var = parseVariable(state.line);
        handleVariable(var, state);
    }

    if (state.rootStruct.first.empty() || state.rootStruct.second.empty()) {
        Fail("Root struct tag [[codegen::Dictionary]] is missing the renderable name");
    }
    std::string resultVerifier = finalizeVerifier(state);
    std::string resultConverter = finalizeConverter(state);

#ifdef PRINT_MEMORY_USAGE
    printf("Memory usage (Buffer: %zi)\n", bufferSize);
    printf("Converter: %lli\n", state.resultConverter - resultConverterBase);
    printf("Verifier: %lli\n", state.resultVerifier - resultVerifierBase);
    printf("Scratch: %lli\n", state.scratchSpace - scratchSpaceBase);
#endif // PRINT_MEMORY_USAGE
}

int main(int argc, char** argv) {
    if (argc != 3) {
        Fail("Wrong number of parameters. Expected %i got %i", 3, argc);
    }

    std::string_view type = argv[1];
    std::string_view src = argv[2];


    //auto before = std::chrono::high_resolution_clock::now();
    handleFile(src);
    //auto after = std::chrono::high_resolution_clock::now();
    //std::cout <<
    //    std::chrono::duration_cast<std::chrono::microseconds>(after - before).count() << 
    //    '\n';
}
