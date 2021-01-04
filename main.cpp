#include <array>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
#include <string_view>
#include <unordered_map>

namespace {
    constexpr const char AttributeDictionary[] = "[[codegen::Dictionary]]";
    constexpr const int ErrorContext = 50;
} // namespace

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

std::string join(const std::vector<std::string_view>& list) {
    size_t size = list.size();
    for (std::string_view l : list) {
        size += l.size();
    }

    std::string res;
    res.reserve(size + 1);
    for (std::string_view l : list) {
        res.append(l.data(), l.size());
        res.append("_");
    }
    res.pop_back();
    return res;
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

std::string verifier(std::string_view type,
                     const std::vector<std::string_view>& structStack)
{
    std::unordered_map<std::string_view, std::string_view> VerifierMapping = {
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

        std::string ver = verifier(subtype, structStack);
        std::array<char, 256> Buf;
        std::fill(Buf.begin(), Buf.end(), '\0');
        int n = sprintf(
            Buf.data(),
            "new TableVerifier({{\"*\",%s,Optional::Yes, \"@TODO\"}})",
            ver.c_str()
        );
        return std::string(Buf.data(), Buf.data() + n);
    }
    else {
        return std::string("codegen_") + join(structStack) + "_" + std::string(type);
    }
}

std::string handleStructStart(const std::vector<std::string_view>& structStack,
                              std::string comment)
{
    std::string name = "codegen_" + join(structStack);

    std::array<char, 512> Buf;
    std::fill(Buf.begin(), Buf.end(), '\0');
    int n = sprintf(Buf.data(), "TableVerifier* %s = new TableVerifier;", name.c_str());
    return std::string(Buf.data(), Buf.data() + n);
}

std::string handleVariable(std::string_view type, std::string_view name,
                           std::string_view attributes,
                           const std::vector<std::string_view>& structStack,
                           std::string comment)
{
    std::string ver = std::string("codegen_") + join(structStack);
    std::string variableName = std::string(name);
    variableName[0] = static_cast<char>(::toupper(variableName[0]));

    if (size_t it = comment.find("codegen::description"); it != std::string::npos) {
        const size_t l = std::string_view("codegen::description").size();
        it += l;
        if (comment[it] != '(') {
            printf(
                "Malformed codegen::description. Expected ( after token:\n%s", 
                comment.c_str()
            );
            exit(EXIT_FAILURE);
        }
        it++;
        size_t end = comment.find(')', it);
        std::string identifier = comment.substr(it, end - it);
        comment = identifier + ".description";
    }
    else {
        comment = std::string("\"") + comment + "\"";
    }

    bool isOptional = false;
    if (startsWith(type, "std::optional<")) {
        isOptional = true;
        type.remove_prefix(std::string_view("std::optional<").size());
        type.remove_suffix(1);
    }

    std::string v = verifier(type, structStack);
    std::array<char, 512> Buffer;
    std::fill(Buffer.begin(), Buffer.end(), '\0');
    int n = sprintf(
        Buffer.data(),
        "%s->documentations.push_back({\"%s\", %s, %s, %s});",
        ver.c_str(), variableName.c_str(), v.c_str(),
        isOptional ? "Optional::Yes" : "Optional::No", comment.c_str()
    );
    return std::string(Buffer.data(), Buffer.data() + n);
}

std::string_view validCode(std::string_view code) {
    const size_t mainLocation = code.find(AttributeDictionary);
    if (code.find(AttributeDictionary, mainLocation + 1) != std::string_view::npos) {
        printf("We currently only support one struct per file annotated with %s, "
            "including commented out ones", AttributeDictionary);
        exit(EXIT_FAILURE);
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
        printf("Could not open file %s", std::string(path).c_str());
        exit(EXIT_FAILURE);
    }

    std::ifstream f(path);
    std::string str(std::istreambuf_iterator<char>{f}, {});
    std::string_view content = strip(validCode(str));
    
    if (std::string_view s = content.substr(0, 6); s != "struct") {
        printf(
            "[[codegen::Dictionary]] needs a 'struct' declaration immediately before on "
            "the same line. Found %s", std::string(s).c_str()
        );
        exit(EXIT_FAILURE);
    }

    if (size_t p = content.find("/*"); p != std::string_view::npos) {
        printf(
            "Block comments are currently not allowed:\n%s",
            std::string(content.substr(p, ErrorContext)).c_str()
        );
        exit(EXIT_FAILURE);
    }

    size_t cursor = 0;
    std::string commentBuffer;
    std::vector<std::string_view> structStack;
    std::string resultVerifier;
    std::string resultConverter;
    while (cursor != std::string_view::npos) {
        std::string_view line = extractLine(content, &cursor);
        if (line.empty()) {
            continue;
        }

        if (startsWith(line, "//")) {
            std::string_view comment = strip(line.substr(2));
            commentBuffer.append(comment);
            continue;
        }

        if (startsWith(line, "struct")) {
            const size_t p1 = line.rfind(' ');
            const size_t p2 = line.rfind(' ', p1 - 1);
            if (p2 == std::string_view::npos) {
                printf(
                    "Missing space before the closing { of a struct:\n%s",
                    std::string(line).c_str()
                );
                exit(EXIT_FAILURE);
            }
            std::string_view structName = line.substr(p2 + 1, p1 - p2 - 1);


            structStack.push_back(structName);
            
            std::string gen = handleStructStart(structStack, commentBuffer);
            resultVerifier.append(std::move(gen));
            continue;
        }

        if (startsWith(line, "};")) {
            if (!commentBuffer.empty()) {
                printf("Unaccounted for comments at the end of a struct definition");
                exit(EXIT_FAILURE);
            }

            std::string_view structName = structStack.back();
            structStack.pop_back();

            // handleStructEnd

            if (structStack.empty()) {
                printf("Finished");
                break;
            }
            continue;
        }

        // If we got this far, we must be in a variable definition
        if (line.back() != ';') {
            printf(
                "We do not support variable definitions over multiple lines:\n%s", 
                std::string(line).c_str()
            );
            exit(EXIT_FAILURE);
        }
        // Remove the trailing ;
        line.remove_suffix(1);

        const size_t p1 = line.find(' ');
        const size_t p2 = line.find(' ', p1 + 1);
        if (p1 == std::string_view::npos) {
            printf(
                "Too few spaces in variable definition:\n%s", std::string(line).c_str()
            );
            exit(EXIT_FAILURE);
        }


        std::string_view type = line.substr(0, p1);
        std::string_view variable = line.substr(p1 + 1, p2);
        std::string_view attributes;
        if (p2 != std::string_view::npos) {
            attributes = line.substr(p2 + 1);
        }

        std::string gen = handleVariable(
            type, variable, attributes, structStack, commentBuffer
        );
        resultVerifier.append(std::move(gen));
        commentBuffer.clear();
    }

    resultVerifier;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Wrong number of parameters. Expected %i got %i", 3, argc);
        exit(EXIT_FAILURE);
    }

    std::string_view type = argv[1];
    std::string_view src = argv[2];



    handleFile(src);
}
