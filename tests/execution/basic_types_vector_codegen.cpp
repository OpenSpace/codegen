// This file has been auto-generated by the codegen tool
//
// Do not change this file manually as any change will be automatically overwritten,
// instead change the struct tagged with "codegen::Dictionary" in the main file from which
// the code in this file was generated.
//
// If a compiler error brought you here, a struct tagged with "codegen::Dictionary"
// was changed without the codegen tool being run again.

namespace codegen {
template <typename T> openspace::documentation::Documentation doc() {
    static_assert(sizeof(T) == 0); // This should never be called
    return openspace::documentation::Documentation();
}
template <> openspace::documentation::Documentation doc<openspace::BasicTypesVector>() {
    using namespace openspace::documentation;
    TableVerifier* codegen_Parameters = new TableVerifier;
    codegen_Parameters->documentations.push_back({"BoolValue",new TableVerifier({{"*",new BoolVerifier,Optional::Yes, }})
,Optional::No,"bool value documentation"});
    codegen_Parameters->documentations.push_back({"IntValue",new TableVerifier({{"*",new IntVerifier,Optional::Yes, }})
,Optional::No,"int value documentation"});
    codegen_Parameters->documentations.push_back({"DoubleValue",new TableVerifier({{"*",new DoubleVerifier,Optional::Yes, }})
,Optional::No,"double value documentation"});
    codegen_Parameters->documentations.push_back({"FloatValue",new TableVerifier({{"*",new DoubleVerifier,Optional::Yes, }})
,Optional::No,"float value documentation"});
    codegen_Parameters->documentations.push_back({"StringValue",new TableVerifier({{"*",new StringVerifier,Optional::Yes, }})
,Optional::No,"string value documentation"});
    codegen_Parameters->documentations.push_back({"Ivec2Value",new TableVerifier({{"*",new IntVector2Verifier,Optional::Yes, }})
,Optional::No,"ivec2 value documentation"});
    codegen_Parameters->documentations.push_back({"Ivec3Value",new TableVerifier({{"*",new IntVector3Verifier,Optional::Yes, }})
,Optional::No,"ivec3 value documentation"});
    codegen_Parameters->documentations.push_back({"Ivec4Value",new TableVerifier({{"*",new IntVector4Verifier,Optional::Yes, }})
,Optional::No,"ivec4 value documentation"});
    codegen_Parameters->documentations.push_back({"Dvec2Value",new TableVerifier({{"*",new DoubleVector2Verifier,Optional::Yes, }})
,Optional::No,"dvec2 value documentation"});
    codegen_Parameters->documentations.push_back({"Dvec3Value",new TableVerifier({{"*",new DoubleVector3Verifier,Optional::Yes, }})
,Optional::No,"dvec3 value documentation"});
    codegen_Parameters->documentations.push_back({"Dvec4Value",new TableVerifier({{"*",new DoubleVector4Verifier,Optional::Yes, }})
,Optional::No,"dvec4 value documentation"});
    codegen_Parameters->documentations.push_back({"Vec2Value",new TableVerifier({{"*",new DoubleVector2Verifier,Optional::Yes, }})
,Optional::No,"vec2 value documentation"});
    codegen_Parameters->documentations.push_back({"Vec3Value",new TableVerifier({{"*",new DoubleVector3Verifier,Optional::Yes, }})
,Optional::No,"vec3 value documentation"});
    codegen_Parameters->documentations.push_back({"Vec4Value",new TableVerifier({{"*",new DoubleVector4Verifier,Optional::Yes, }})
,Optional::No,"vec4 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat2x2Value",new TableVerifier({{"*",new DoubleMatrix2x2Verifier,Optional::Yes, }})
,Optional::No,"mat2x2 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat2x3Value",new TableVerifier({{"*",new DoubleMatrix2x3Verifier,Optional::Yes, }})
,Optional::No,"mat2x3 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat2x4Value",new TableVerifier({{"*",new DoubleMatrix2x4Verifier,Optional::Yes, }})
,Optional::No,"mat2x4 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat3x2Value",new TableVerifier({{"*",new DoubleMatrix3x2Verifier,Optional::Yes, }})
,Optional::No,"mat3x2 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat3x3Value",new TableVerifier({{"*",new DoubleMatrix3x3Verifier,Optional::Yes, }})
,Optional::No,"mat3x3 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat3x4Value",new TableVerifier({{"*",new DoubleMatrix3x4Verifier,Optional::Yes, }})
,Optional::No,"mat3x4 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat4x2Value",new TableVerifier({{"*",new DoubleMatrix4x2Verifier,Optional::Yes, }})
,Optional::No,"mat4x2 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat4x3Value",new TableVerifier({{"*",new DoubleMatrix4x3Verifier,Optional::Yes, }})
,Optional::No,"mat4x3 value documentation"});
    codegen_Parameters->documentations.push_back({"Mat4x4Value",new TableVerifier({{"*",new DoubleMatrix4x4Verifier,Optional::Yes, }})
,Optional::No,"mat4x4 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat2x2Value",new TableVerifier({{"*",new DoubleMatrix2x2Verifier,Optional::Yes, }})
,Optional::No,"dmat2x2 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat2x3Value",new TableVerifier({{"*",new DoubleMatrix2x3Verifier,Optional::Yes, }})
,Optional::No,"dmat2x3 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat2x4Value",new TableVerifier({{"*",new DoubleMatrix2x4Verifier,Optional::Yes, }})
,Optional::No,"dmat2x4 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat3x2Value",new TableVerifier({{"*",new DoubleMatrix3x2Verifier,Optional::Yes, }})
,Optional::No,"dmat3x2 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat3x3Value",new TableVerifier({{"*",new DoubleMatrix3x3Verifier,Optional::Yes, }})
,Optional::No,"dmat3x3 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat3x4Value",new TableVerifier({{"*",new DoubleMatrix3x4Verifier,Optional::Yes, }})
,Optional::No,"dmat3x4 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat4x2Value",new TableVerifier({{"*",new DoubleMatrix4x2Verifier,Optional::Yes, }})
,Optional::No,"dmat4x2 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat4x3Value",new TableVerifier({{"*",new DoubleMatrix4x3Verifier,Optional::Yes, }})
,Optional::No,"dmat4x3 value documentation"});
    codegen_Parameters->documentations.push_back({"Dmat4x4Value",new TableVerifier({{"*",new DoubleMatrix4x4Verifier,Optional::Yes, }})
,Optional::No,"dmat4x4 value documentation"});

    openspace::documentation::Documentation d = { "BasicTypesVector", "BasicTypesVector", std::move(codegen_Parameters->documentations) };
    delete codegen_Parameters;
    return d;
}
} // namespace codegen


namespace codegen {
namespace internal {
template<typename T> void bakeTo(const ghoul::Dictionary&, std::string_view, T*) { static_assert(sizeof(T) == 0); } // This should never be called
void bakeTo(const ghoul::Dictionary& d, std::string_view key, bool* val) { *val = d.value<bool>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, double* val) { *val = d.value<double>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, float* val) { *val = static_cast<float>(d.value<double>(key)); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x2* val) { *val = d.value<glm::dmat2x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x3* val) { *val = d.value<glm::dmat2x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat2x4* val) { *val = d.value<glm::dmat2x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x2* val) { *val = d.value<glm::dmat3x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x3* val) { *val = d.value<glm::dmat3x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat3x4* val) { *val = d.value<glm::dmat3x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x2* val) { *val = d.value<glm::dmat4x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x3* val) { *val = d.value<glm::dmat4x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dmat4x4* val) { *val = d.value<glm::dmat4x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec2* val) { *val = d.value<glm::dvec2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec3* val) { *val = d.value<glm::dvec3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::dvec4* val) { *val = d.value<glm::dvec4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec2* val) { *val = d.value<glm::dvec2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec3* val) { *val = d.value<glm::dvec3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::ivec4* val) { *val = d.value<glm::dvec4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x2* val) { *val = d.value<glm::dmat2x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x3* val) { *val = d.value<glm::dmat2x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat2x4* val) { *val = d.value<glm::dmat2x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x2* val) { *val = d.value<glm::dmat3x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x3* val) { *val = d.value<glm::dmat3x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat3x4* val) { *val = d.value<glm::dmat3x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x2* val) { *val = d.value<glm::dmat4x2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x3* val) { *val = d.value<glm::dmat4x3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::mat4x4* val) { *val = d.value<glm::dmat4x4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec2* val) { *val = d.value<glm::dvec2>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec3* val) { *val = d.value<glm::dvec3>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, glm::vec4* val) { *val = d.value<glm::dvec4>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, int* val) { *val = static_cast<int>(d.value<double>(key)); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::string* val) { *val = d.value<std::string>(key); }
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val);

template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val) {
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    std::vector<std::string_view> keys = dict.keys();
    val->reserve(keys.size());
    for (size_t i = 0; i < dict.size(); ++i) {
        T v;
        bakeTo(dict, keys[i], &v);
        val->push_back(std::move(v));
    }
}

} // namespace internal

template <typename T> T bake(const ghoul::Dictionary&) { static_assert(sizeof(T) == 0); }
template <> Parameters bake<Parameters>(const ghoul::Dictionary& dict) {
    openspace::documentation::testSpecificationAndThrow(codegen::doc<openspace::BasicTypesVector>(), dict, "BasicTypesVector");
    Parameters res;
    internal::bakeTo(dict, "BoolValue", &res.boolValue);
    internal::bakeTo(dict, "IntValue", &res.intValue);
    internal::bakeTo(dict, "DoubleValue", &res.doubleValue);
    internal::bakeTo(dict, "FloatValue", &res.floatValue);
    internal::bakeTo(dict, "StringValue", &res.stringValue);
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
    internal::bakeTo(dict, "Mat2x3Value", &res.mat2x3Value);
    internal::bakeTo(dict, "Mat2x4Value", &res.mat2x4Value);
    internal::bakeTo(dict, "Mat3x2Value", &res.mat3x2Value);
    internal::bakeTo(dict, "Mat3x3Value", &res.mat3x3Value);
    internal::bakeTo(dict, "Mat3x4Value", &res.mat3x4Value);
    internal::bakeTo(dict, "Mat4x2Value", &res.mat4x2Value);
    internal::bakeTo(dict, "Mat4x3Value", &res.mat4x3Value);
    internal::bakeTo(dict, "Mat4x4Value", &res.mat4x4Value);
    internal::bakeTo(dict, "Dmat2x2Value", &res.dmat2x2Value);
    internal::bakeTo(dict, "Dmat2x3Value", &res.dmat2x3Value);
    internal::bakeTo(dict, "Dmat2x4Value", &res.dmat2x4Value);
    internal::bakeTo(dict, "Dmat3x2Value", &res.dmat3x2Value);
    internal::bakeTo(dict, "Dmat3x3Value", &res.dmat3x3Value);
    internal::bakeTo(dict, "Dmat3x4Value", &res.dmat3x4Value);
    internal::bakeTo(dict, "Dmat4x2Value", &res.dmat4x2Value);
    internal::bakeTo(dict, "Dmat4x3Value", &res.dmat4x3Value);
    internal::bakeTo(dict, "Dmat4x4Value", &res.dmat4x4Value);
    return res;
}
} // namespace codegen