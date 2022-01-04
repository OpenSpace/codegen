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
    std::shared_ptr<TableVerifier> codegen_Parameters_A = std::make_shared<TableVerifier>();
    codegen_Parameters_A->documentations.push_back({"Value",new IntVerifier,Optional::No,"A::value documentation"});
    std::shared_ptr<TableVerifier> codegen_Parameters_B = std::make_shared<TableVerifier>();
    codegen_Parameters_B->documentations.push_back({"Valval",new DoubleVerifier,Optional::No,"B::valval documentation"});
    std::shared_ptr<TableVerifier> codegen_Parameters_C = std::make_shared<TableVerifier>();
    codegen_Parameters_C->documentations.push_back({"Eulav",new StringVerifier,Optional::No,"C::eulav documentation"});
    codegen_Parameters_C->documentations.push_back({"Lavlav",new BoolVerifier,Optional::No,"C::lavlav documentation"});
    std::shared_ptr<TableVerifier> codegen_Parameters_D = std::make_shared<TableVerifier>();
    codegen_Parameters_D->documentations.push_back({"A",new StringVerifier,Optional::No,"D::a documentation"});
    codegen_Parameters_D->documentations.push_back({"B",new IntVerifier,Optional::No,"D::b docuimentation"});
    codegen_Parameters->documentations.push_back({"StructAValue",codegen_Parameters_A,Optional::No,"variable structAValue documentation"});
    codegen_Parameters->documentations.push_back({"StructBValue",codegen_Parameters_B,Optional::Yes,"variable structBValue documentation"});
    codegen_Parameters->documentations.push_back({"StructCValue",new TableVerifier({{"*",codegen_Parameters_C,Optional::Yes, "struct C documentation"}})
,Optional::No,"variable structCValue documentation"});
    codegen_Parameters->documentations.push_back({"StructDValue",codegen_Parameters_D,Optional::No,"variable structDValue documentation"});
    codegen_Parameters->documentations.push_back({"StructDVectorValue",new TableVerifier({{"*",codegen_Parameters_D,Optional::Yes, "struct D documentation"}})
,Optional::No,"variable structDVectorValue documentation"});
    codegen_Parameters->documentations.push_back({"StructDOptionalValue",codegen_Parameters_D,Optional::Yes,"variable structDOptionalValue documentation"});

    openspace::documentation::Documentation d = { "Substructs", std::move(id), std::move(codegen_Parameters->documentations) };
    return d;
}

} // namespace codegen

namespace codegen {
namespace internal { 
template<typename T> void bakeTo(const ghoul::Dictionary&, std::string_view, T*) { static_assert(sizeof(T) == 0); }
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val);
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val);
void bakeTo(const ghoul::Dictionary& d, std::string_view key, int* val) { if (d.hasValue<double>(key)) { *val = static_cast<int>(d.value<double>(key)); } else if (d.hasValue<int>(key)) { *val = d.value<int>(key); } else { throw std::logic_error("Unexpected type"); } }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, float* val) { *val = static_cast<float>(d.value<double>(key)); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::string* val) { *val = d.value<std::string>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, bool* val) { *val = d.value<bool>(key); }
template <> void bakeTo<Parameters::A>(const ghoul::Dictionary& d, std::string_view key, Parameters::A* val) {
    Parameters::A& res = *val;
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    internal::bakeTo(dict, "Value", &res.value);
}
template <> void bakeTo<Parameters::B>(const ghoul::Dictionary& d, std::string_view key, Parameters::B* val) {
    Parameters::B& res = *val;
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    internal::bakeTo(dict, "Valval", &res.valval);
}
template <> void bakeTo<Parameters::C>(const ghoul::Dictionary& d, std::string_view key, Parameters::C* val) {
    Parameters::C& res = *val;
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    internal::bakeTo(dict, "Eulav", &res.eulav);
    internal::bakeTo(dict, "Lavlav", &res.lavlav);
}
template <> void bakeTo<Parameters::D>(const ghoul::Dictionary& d, std::string_view key, Parameters::D* val) {
    Parameters::D& res = *val;
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    internal::bakeTo(dict, "A", &res.a);
    internal::bakeTo(dict, "B", &res.b);
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
    openspace::documentation::testSpecificationAndThrow(codegen::doc<Parameters>("Parameters"), dict, "Substructs");
    Parameters res;
    internal::bakeTo(dict, "StructAValue", &res.structAValue);
    internal::bakeTo(dict, "StructBValue", &res.structBValue);
    internal::bakeTo(dict, "StructCValue", &res.structCValue);
    internal::bakeTo(dict, "StructDValue", &res.structDValue);
    internal::bakeTo(dict, "StructDVectorValue", &res.structDVectorValue);
    internal::bakeTo(dict, "StructDOptionalValue", &res.structDOptionalValue);
    return res;
}

}// namespace codegen