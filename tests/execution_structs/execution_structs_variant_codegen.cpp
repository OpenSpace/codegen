// This file has been auto-generated by the codegen tool
//
// Do not change this file manually as any change will be automatically overwritten,
// instead change the struct tagged with "codegen::Dictionary" in the main file from which
// the code in this file was generated.
//
// If a compiler error brought you here, a struct tagged with "codegen::Dictionary"
// was changed without the codegen tool being run again.
namespace codegen {
template<typename T> openspace::documentation::Documentation doc(std::string) {
    static_assert(sizeof(T) == 0);
    return openspace::documentation::Documentation();
}
template <> openspace::documentation::Documentation doc<Parameters>(std::string id) {
    using namespace openspace::documentation;

    TableVerifier codegen_Parameters_content;
    TableVerifier* codegen_Parameters = &codegen_Parameters_content;
    std::shared_ptr<StringInListVerifier> codegen_Parameters_A = std::make_shared<StringInListVerifier>(std::vector<std::string>{"Value1","Value2","Value3"});
    std::shared_ptr<StringInListVerifier> codegen_Parameters_B = std::make_shared<StringInListVerifier>(std::vector<std::string>{"Value1","Value2","Value3"});
    codegen_Parameters->documentations.push_back({"BoolDoubleValue",new OrVerifier({new BoolVerifier,new DoubleVerifier}),Optional::No,"boolDouble value documentation"});
    codegen_Parameters->documentations.push_back({"FloatStringValue",new OrVerifier({new DoubleVerifier,new StringVerifier}),Optional::No,"floatString value documentation"});
    codegen_Parameters->documentations.push_back({"IvecsValue",new OrVerifier({new IntVector2Verifier,new IntVector3Verifier,new IntVector4Verifier}),Optional::No,"ivecs value documentation"});
    codegen_Parameters->documentations.push_back({"Vecmat1",new OrVerifier({new DoubleVector2Verifier,new DoubleVector3Verifier,new DoubleVector4Verifier,new DoubleMatrix2x3Verifier,new DoubleMatrix4x2Verifier,new DoubleMatrix4x4Verifier}),Optional::No,"vecmat1 value documentation"});
    codegen_Parameters->documentations.push_back({"Vecmat2",new OrVerifier({new DoubleMatrix2x2Verifier,new DoubleMatrix3x3Verifier,new DoubleMatrix2x4Verifier}),Optional::No,"vecmat2 value documentation"});
    codegen_Parameters->documentations.push_back({"RestValue",new OrVerifier({new DoubleVector2Verifier,new DoubleVector3Verifier,new DoubleVector4Verifier,new DoubleMatrix2x3Verifier,new DoubleMatrix2x4Verifier,new DoubleMatrix3x3Verifier,new DoubleMatrix3x4Verifier,new DoubleMatrix4x4Verifier}),Optional::No,"rest value documentation"});
    codegen_Parameters->documentations.push_back({"OptionalValue",new OrVerifier({new BoolVerifier,new IntVerifier}),Optional::Yes,"optional documentation"});
    codegen_Parameters->documentations.push_back({"VariantVector",new OrVerifier({new TableVerifier({{"*",new StringVerifier,Optional::Yes, }})
,new StringVerifier}),Optional::No,"variant vector documentation"});
    codegen_Parameters->documentations.push_back({"VariantVector2",new OrVerifier({new StringVerifier,new TableVerifier({{"*",new StringVerifier,Optional::Yes, }})
}),Optional::No,"variant vector 2 documentation"});
    codegen_Parameters->documentations.push_back({"MultipleVariantA",new OrVerifier({new IntVerifier,new StringVerifier}),Optional::No,"multiple variant a documentation"});
    codegen_Parameters->documentations.push_back({"MultipleVariantB",new OrVerifier({new StringVerifier,new IntVerifier}),Optional::No,"multiple variant b documentation"});
    codegen_Parameters->documentations.push_back({"MultipleVariantA2",new OrVerifier({new IntVerifier,new StringVerifier}),Optional::No,"multiple variant a2 documentation"});
    codegen_Parameters->documentations.push_back({"MultipleVariantB2",new OrVerifier({new StringVerifier,new IntVerifier}),Optional::Yes,"multiple variant b2 documentation"});
    codegen_Parameters->documentations.push_back({"VariantEnumFloat",new OrVerifier({codegen_Parameters_A,new DoubleVerifier}),Optional::No,"variant enum float documentation"});
    codegen_Parameters->documentations.push_back({"OptionalVariantEnumFloat",new OrVerifier({codegen_Parameters_B,new DoubleVerifier}),Optional::Yes,"optional variant enum float documentation"});

    openspace::documentation::Documentation d = { "Variant", std::move(id), std::move(codegen_Parameters->documentations) };
    return d;
}

} // namespace codegen

namespace codegen {
namespace internal {
template<typename T> void bakeTo(const ghoul::Dictionary&, std::string_view, T*) { static_assert(sizeof(T) == 0); }
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val);
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val);
void bakeTo(const ghoul::Dictionary& d, std::string_view key, bool* val) { *val = d.value<bool>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, double* val) { *val = d.value<double>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, float* val) { *val = static_cast<float>(d.value<double>(key)); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::string* val) { *val = d.value<std::string>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec2* val) { *val = d.value<glm::dvec2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec3* val) { *val = d.value<glm::dvec3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec4* val) { *val = d.value<glm::dvec4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec2* val) { *val = d.value<glm::dvec2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec3* val) { *val = d.value<glm::dvec3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec4* val) { *val = d.value<glm::dvec4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x3* val) { *val = d.value<glm::dmat2x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x2* val) { *val = d.value<glm::dmat4x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x4* val) { *val = d.value<glm::dmat4x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x2* val) { *val = d.value<glm::dmat2x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x3* val) { *val = d.value<glm::dmat3x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x4* val) { *val = d.value<glm::dmat2x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec2* val) { *val = d.value<glm::dvec2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec3* val) { *val = d.value<glm::dvec3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec4* val) { *val = d.value<glm::dvec4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x3* val) { *val = d.value<glm::dmat3x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x4* val) { *val = d.value<glm::dmat3x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x4* val) { *val = d.value<glm::dmat4x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, int* val) { if (d.hasValue<double>(key)) { *val = static_cast<int>(d.value<double>(key)); } else if (d.hasValue<int>(key)) { *val = d.value<int>(key); } else { throw std::logic_error("Unexpected type"); } }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, Parameters::A* val) {
    std::string v = d.value<std::string>(key);
    if (v == "Value1") { *val = Parameters::A::Value1; }
    if (v == "Value2") { *val = Parameters::A::Value2; }
    if (v == "Value3") { *val = Parameters::A::Value3; }
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, Parameters::B* val) {
    std::string v = d.value<std::string>(key);
    if (v == "Value1") { *val = Parameters::B::Value1; }
    if (v == "Value2") { *val = Parameters::B::Value2; }
    if (v == "Value3") { *val = Parameters::B::Value3; }
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<bool, double>* val) {
   if (d.hasValue<bool>(key)) { bool v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<double>(key)) { double v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<float, std::string>* val) {
   if (d.hasValue<double>(key)) { float v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<std::string>(key)) { std::string v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<glm::ivec2, glm::ivec3, glm::ivec4>* val) {
   if (d.hasValue<glm::dvec2>(key)) { glm::ivec2 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dvec3>(key)) { glm::ivec3 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dvec4>(key)) { glm::ivec4 v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<glm::dvec2, glm::dvec3, glm::dvec4, glm::mat2x3, glm::mat4x2, glm::dmat4x4>* val) {
   if (d.hasValue<glm::dvec2>(key)) { glm::dvec2 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dvec3>(key)) { glm::dvec3 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dvec4>(key)) { glm::dvec4 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dmat2x3>(key)) { glm::mat2x3 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dmat4x2>(key)) { glm::mat4x2 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dmat4x4>(key)) { glm::dmat4x4 v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<glm::mat2x2, glm::dmat3x3, glm::mat2x4>* val) {
   if (d.hasValue<glm::dmat2x2>(key)) { glm::mat2x2 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dmat3x3>(key)) { glm::dmat3x3 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dmat2x4>(key)) { glm::mat2x4 v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<glm::vec2, glm::vec3, glm::vec4, glm::mat2x3, glm::mat2x4, glm::mat3x3, glm::mat3x4, glm::mat4x4>* val) {
   if (d.hasValue<glm::dvec2>(key)) { glm::vec2 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dvec3>(key)) { glm::vec3 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dvec4>(key)) { glm::vec4 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dmat2x3>(key)) { glm::mat2x3 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dmat2x4>(key)) { glm::mat2x4 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dmat3x3>(key)) { glm::mat3x3 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dmat3x4>(key)) { glm::mat3x4 v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<glm::dmat4x4>(key)) { glm::mat4x4 v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<bool, int>* val) {
   if (d.hasValue<bool>(key)) { bool v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<double>(key)) { int v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<std::vector<std::string>, std::string>* val) {
   if (d.hasValue<ghoul::Dictionary>(key)) { std::vector<std::string> v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<std::string>(key)) { std::string v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<std::string, std::vector<std::string>>* val) {
   if (d.hasValue<std::string>(key)) { std::string v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<ghoul::Dictionary>(key)) { std::vector<std::string> v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<int, std::string>* val) {
   if (d.hasValue<double>(key)) { int v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<std::string>(key)) { std::string v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<std::string, int>* val) {
   if (d.hasValue<std::string>(key)) { std::string v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<double>(key)) { int v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<Parameters::A, float>* val) {
   if (d.hasValue<std::string>(key)) { Parameters::A v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<double>(key)) { float v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::variant<Parameters::B, float>* val) {
   if (d.hasValue<std::string>(key)) { Parameters::B v; bakeTo(d, key, &v); *val = std::move(v); return; }
   if (d.hasValue<double>(key)) { float v; bakeTo(d, key, &v); *val = std::move(v); return; }
    // Any of the previous values should have triggered and returned
    // If this assert triggers, something in the codegen went wrong
    assert(false);
}

template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val) {
    if (d.hasKey(key)) {
        T v;
        bakeTo(d, key, &v);
        *val = v;
    }
    else {
        *val = std::nullopt;
    }
}

template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val) {
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    // For the moment we need to make sure in here that all of the keys are sequential
    // since our TableVerifier doesn't really do that and we don't have a VectorVerifier
    // for a flat list (yet).  So you might have gotten a specification error from here
    // iff the Dictionary that was passed in contained keys other than a linear sequence
    // from 1 - dict.size()  [1 because Lua for some strange reason wants to start at the
    // wrong number]

    for (size_t i = 1; i <= dict.size(); ++i) {
        std::string k = std::to_string(i);
        if (!dict.hasKey(k)) {
            throw std::runtime_error("Could not find key '" + k + "' in the dictionary");
        }
    }    

    for (size_t i = 1; i <= dict.size(); ++i) {
        T v;
        bakeTo(dict, std::to_string(i), &v);
        val->push_back(std::move(v));
    }
}

} // namespace internal

template <typename T> T bake(const ghoul::Dictionary&) { static_assert(sizeof(T) == 0); }

template <> Parameters bake<Parameters>(const ghoul::Dictionary& dict) {
    openspace::documentation::testSpecificationAndThrow(codegen::doc<Parameters>("Parameters"), dict, "Variant");
    Parameters res;
    internal::bakeTo(dict, "BoolDoubleValue", &res.boolDoubleValue);
    internal::bakeTo(dict, "FloatStringValue", &res.floatStringValue);
    internal::bakeTo(dict, "IvecsValue", &res.ivecsValue);
    internal::bakeTo(dict, "Vecmat1", &res.vecmat1);
    internal::bakeTo(dict, "Vecmat2", &res.vecmat2);
    internal::bakeTo(dict, "RestValue", &res.restValue);
    internal::bakeTo(dict, "OptionalValue", &res.optionalValue);
    internal::bakeTo(dict, "VariantVector", &res.variantVector);
    internal::bakeTo(dict, "VariantVector2", &res.variantVector2);
    internal::bakeTo(dict, "MultipleVariantA", &res.multipleVariantA);
    internal::bakeTo(dict, "MultipleVariantB", &res.multipleVariantB);
    internal::bakeTo(dict, "MultipleVariantA2", &res.multipleVariantA2);
    internal::bakeTo(dict, "MultipleVariantB2", &res.multipleVariantB2);
    internal::bakeTo(dict, "VariantEnumFloat", &res.variantEnumFloat);
    internal::bakeTo(dict, "OptionalVariantEnumFloat", &res.optionalVariantEnumFloat);
    return res;
}

}// namespace codegen
