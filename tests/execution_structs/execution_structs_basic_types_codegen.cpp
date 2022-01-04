// This file has been auto-generated by the codegen tool
//
// Under **no** circumstances change this file manually as any change will be
// automatically overwritten. Instead change the struct tagged with "codegen::Dictionary"
// or the enum class tagged with "codegen::stringify" in the main file from which he code
// in this file was generated.
//
// If a compiler error brought you into this file, a struct tagged with
// "codegen::Dictionary" or an enum class tagged with "codegen::stringify" was changed
// without the codegen tool being run again.

namespace codegen {
template<typename T> openspace::documentation::Documentation doc(std::string) {
    static_assert(sizeof(T) == 0);
    return openspace::documentation::Documentation();
}
template <> openspace::documentation::Documentation doc<Parameters>(std::string id) {
    using namespace openspace::documentation;

    TableVerifier codegen_Parameters_content;
    TableVerifier* codegen_Parameters = &codegen_Parameters_content;
    codegen_Parameters->documentations.push_back({"BoolValue",new BoolVerifier,Optional::No,"bool value documentation"});
    codegen_Parameters->documentations.push_back({"IntValue",new IntVerifier,Optional::No,"int value documentation"});
    codegen_Parameters->documentations.push_back({"IntValue2",new IntVerifier,Optional::No,"int value 2 documentation"});
    codegen_Parameters->documentations.push_back({"DoubleValue",new DoubleVerifier,Optional::No,"double value documentation"});
    codegen_Parameters->documentations.push_back({"FloatValue",new DoubleVerifier,Optional::No,"float value documentation"});
    codegen_Parameters->documentations.push_back({"StringValue",new StringVerifier,Optional::No,"string value documentation"});
    codegen_Parameters->documentations.push_back({"StringNotEmptyValue",new StringVerifier(true),Optional::No,"string not empty value documentation"});
    codegen_Parameters->documentations.push_back({"PathValue",new FileVerifier,Optional::No,"path value documentation"});
    codegen_Parameters->documentations.push_back({"DirectoryValue",new DirectoryVerifier,Optional::No,"directory value documentation"});
    codegen_Parameters->documentations.push_back({"Ivec2Value",new IntVector2Verifier,Optional::No,"ivec2 value documentation"});
    codegen_Parameters->documentations.push_back({"Ivec3Value",new IntVector3Verifier,Optional::No,"ivec3 value documentation"});
    codegen_Parameters->documentations.push_back({"Ivec4Value",new IntVector4Verifier,Optional::No,"ivec4 value documentation"});
    codegen_Parameters->documentations.push_back({"Dvec2Value",new DoubleVector2Verifier,Optional::No,"dvec2 value documentation"});
    codegen_Parameters->documentations.push_back({"Dvec3Value",new DoubleVector3Verifier,Optional::No,"dvec3 value documentation"});
    codegen_Parameters->documentations.push_back({"Dvec4Value",new DoubleVector4Verifier,Optional::No,"dvec4 value documentation"});
    codegen_Parameters->documentations.push_back({"Vec2Value",new DoubleVector2Verifier,Optional::No,"vec2 value documentation"});
    codegen_Parameters->documentations.push_back({"Vec3Value",new DoubleVector3Verifier,Optional::No,"vec3 value documentation"});
    codegen_Parameters->documentations.push_back({"Vec4Value",new DoubleVector4Verifier,Optional::No,"vec4 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat2x2Value",new DoubleMatrix2x2Verifier,Optional::No,"mat2x2 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat2Value",new DoubleMatrix2x2Verifier,Optional::No,"mat2 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat2x3Value",new DoubleMatrix2x3Verifier,Optional::No,"mat2x3 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat2x4Value",new DoubleMatrix2x4Verifier,Optional::No,"mat2x4 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat3x2Value",new DoubleMatrix3x2Verifier,Optional::No,"mat3x2 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat3x3Value",new DoubleMatrix3x3Verifier,Optional::No,"mat3x3 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat3Value",new DoubleMatrix3x3Verifier,Optional::No,"mat3 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat3x4Value",new DoubleMatrix3x4Verifier,Optional::No,"mat3x4 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat4x2Value",new DoubleMatrix4x2Verifier,Optional::No,"mat4x2 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat4x3Value",new DoubleMatrix4x3Verifier,Optional::No,"mat4x3 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat4x4Value",new DoubleMatrix4x4Verifier,Optional::No,"mat4x4 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat4Value",new DoubleMatrix4x4Verifier,Optional::No,"mat4 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat2x2Value",new DoubleMatrix2x2Verifier,Optional::No,"dmat2x2 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat2Value",new DoubleMatrix2x2Verifier,Optional::No,"dmat2 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat2x3Value",new DoubleMatrix2x3Verifier,Optional::No,"dmat2x3 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat2x4Value",new DoubleMatrix2x4Verifier,Optional::No,"dmat2x4 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat3x2Value",new DoubleMatrix3x2Verifier,Optional::No,"dmat3x2 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat3x3Value",new DoubleMatrix3x3Verifier,Optional::No,"dmat3x3 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat3Value",new DoubleMatrix3x3Verifier,Optional::No,"dmat3 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat3x4Value",new DoubleMatrix3x4Verifier,Optional::No,"dmat3x4 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat4x2Value",new DoubleMatrix4x2Verifier,Optional::No,"dmat4x2 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat4x3Value",new DoubleMatrix4x3Verifier,Optional::No,"dmat4x3 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat4x4Value",new DoubleMatrix4x4Verifier,Optional::No,"dmat4x4 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat4Value",new DoubleMatrix4x4Verifier,Optional::No,"dmat4 value documentation"});
    codegen_Parameters->documentations.push_back({"DictValue",new TableVerifier,Optional::No,"dict value documentation"});

    openspace::documentation::Documentation d = { "BasicTypes", std::move(id), std::move(codegen_Parameters->documentations) };
    return d;
}

} // namespace codegen

namespace codegen {
namespace internal { 
template<typename T> void bakeTo(const ghoul::Dictionary&, std::string_view, T*) { static_assert(sizeof(T) == 0); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, bool* val) { *val = d.value<bool>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, int* val) { if (d.hasValue<double>(key)) { *val = static_cast<int>(d.value<double>(key)); } else if (d.hasValue<int>(key)) { *val = d.value<int>(key); } else { throw std::logic_error("Unexpected type"); } }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, double* val) { *val = d.value<double>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, float* val) { *val = static_cast<float>(d.value<double>(key)); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::string* val) { *val = d.value<std::string>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::filesystem::path* val) { *val = d.value<std::string>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec2* val) { *val = d.value<glm::dvec2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec3* val) { *val = d.value<glm::dvec3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec4* val) { *val = d.value<glm::dvec4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec2* val) { *val = d.value<glm::dvec2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec3* val) { *val = d.value<glm::dvec3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec4* val) { *val = d.value<glm::dvec4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec2* val) { *val = d.value<glm::dvec2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec3* val) { *val = d.value<glm::dvec3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec4* val) { *val = d.value<glm::dvec4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x2* val) { *val = d.value<glm::dmat2x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x3* val) { *val = d.value<glm::dmat2x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x4* val) { *val = d.value<glm::dmat2x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x2* val) { *val = d.value<glm::dmat3x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x3* val) { *val = d.value<glm::dmat3x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x4* val) { *val = d.value<glm::dmat3x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x2* val) { *val = d.value<glm::dmat4x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x3* val) { *val = d.value<glm::dmat4x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x4* val) { *val = d.value<glm::dmat4x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x2* val) { *val = d.value<glm::dmat2x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x3* val) { *val = d.value<glm::dmat2x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x4* val) { *val = d.value<glm::dmat2x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x2* val) { *val = d.value<glm::dmat3x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x3* val) { *val = d.value<glm::dmat3x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x4* val) { *val = d.value<glm::dmat3x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x2* val) { *val = d.value<glm::dmat4x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x3* val) { *val = d.value<glm::dmat4x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x4* val) { *val = d.value<glm::dmat4x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, ghoul::Dictionary* val) { *val = d.value<ghoul::Dictionary>(key); }

} // namespace internal

template <typename T> T bake(const ghoul::Dictionary&) { static_assert(sizeof(T) == 0); }

template <> Parameters bake<Parameters>(const ghoul::Dictionary& dict) {
    openspace::documentation::testSpecificationAndThrow(codegen::doc<Parameters>("Parameters"), dict, "BasicTypes");
    Parameters res;
    internal::bakeTo(dict, "BoolValue", &res.boolValue);
    internal::bakeTo(dict, "IntValue", &res.intValue);
    internal::bakeTo(dict, "IntValue2", &res.intValue2);
    internal::bakeTo(dict, "DoubleValue", &res.doubleValue);
    internal::bakeTo(dict, "FloatValue", &res.floatValue);
    internal::bakeTo(dict, "StringValue", &res.stringValue);
    internal::bakeTo(dict, "StringNotEmptyValue", &res.stringNotEmptyValue);
    internal::bakeTo(dict, "PathValue", &res.pathValue);
    internal::bakeTo(dict, "DirectoryValue", &res.directoryValue);
    internal::bakeTo(dict, "Ivec2Value", &res.ivec2Value);
    internal::bakeTo(dict, "Ivec3Value", &res.ivec3Value);
    internal::bakeTo(dict, "Ivec4Value", &res.ivec4Value);
    internal::bakeTo(dict, "Dvec2Value", &res.dvec2Value);
    internal::bakeTo(dict, "Dvec3Value", &res.dvec3Value);
    internal::bakeTo(dict, "Dvec4Value", &res.dvec4Value);
    internal::bakeTo(dict, "Vec2Value", &res.vec2Value);
    internal::bakeTo(dict, "Vec3Value", &res.vec3Value);
    internal::bakeTo(dict, "Vec4Value", &res.vec4Value);
    internal::bakeTo(dict, "Mat2x2Value", &res.mat2x2Value);
    internal::bakeTo(dict, "Mat2Value", &res.mat2Value);
    internal::bakeTo(dict, "Mat2x3Value", &res.mat2x3Value);
    internal::bakeTo(dict, "Mat2x4Value", &res.mat2x4Value);
    internal::bakeTo(dict, "Mat3x2Value", &res.mat3x2Value);
    internal::bakeTo(dict, "Mat3x3Value", &res.mat3x3Value);
    internal::bakeTo(dict, "Mat3Value", &res.mat3Value);
    internal::bakeTo(dict, "Mat3x4Value", &res.mat3x4Value);
    internal::bakeTo(dict, "Mat4x2Value", &res.mat4x2Value);
    internal::bakeTo(dict, "Mat4x3Value", &res.mat4x3Value);
    internal::bakeTo(dict, "Mat4x4Value", &res.mat4x4Value);
    internal::bakeTo(dict, "Mat4Value", &res.mat4Value);
    internal::bakeTo(dict, "Dmat2x2Value", &res.dmat2x2Value);
    internal::bakeTo(dict, "Dmat2Value", &res.dmat2Value);
    internal::bakeTo(dict, "Dmat2x3Value", &res.dmat2x3Value);
    internal::bakeTo(dict, "Dmat2x4Value", &res.dmat2x4Value);
    internal::bakeTo(dict, "Dmat3x2Value", &res.dmat3x2Value);
    internal::bakeTo(dict, "Dmat3x3Value", &res.dmat3x3Value);
    internal::bakeTo(dict, "Dmat3Value", &res.dmat3Value);
    internal::bakeTo(dict, "Dmat3x4Value", &res.dmat3x4Value);
    internal::bakeTo(dict, "Dmat4x2Value", &res.dmat4x2Value);
    internal::bakeTo(dict, "Dmat4x3Value", &res.dmat4x3Value);
    internal::bakeTo(dict, "Dmat4x4Value", &res.dmat4x4Value);
    internal::bakeTo(dict, "Dmat4Value", &res.dmat4Value);
    internal::bakeTo(dict, "DictValue", &res.dictValue);
    return res;
}

}// namespace codegen