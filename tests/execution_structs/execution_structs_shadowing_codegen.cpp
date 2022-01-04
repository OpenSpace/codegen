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
template <> openspace::documentation::Documentation doc<P>(std::string id) {
    using namespace openspace::documentation;

    TableVerifier codegen_P_content;
    TableVerifier* codegen_P = &codegen_P_content;
    std::shared_ptr<TableVerifier> codegen_P_A = std::make_shared<TableVerifier>();
    std::shared_ptr<StringInListVerifier> codegen_P_A_T = std::make_shared<StringInListVerifier>(std::vector<std::string>{"Type1","Type2"});
    codegen_P_A->documentations.push_back({"T",codegen_P_A_T,Optional::No,""});
    std::shared_ptr<TableVerifier> codegen_P_B = std::make_shared<TableVerifier>();
    std::shared_ptr<StringInListVerifier> codegen_P_B_T = std::make_shared<StringInListVerifier>(std::vector<std::string>{"Type3","Type4"});
    codegen_P_B->documentations.push_back({"T",codegen_P_B_T,Optional::No,""});
    std::shared_ptr<StringInListVerifier> codegen_P_T = std::make_shared<StringInListVerifier>(std::vector<std::string>{"Type5","Type6"});
    std::shared_ptr<TableVerifier> codegen_P_C = std::make_shared<TableVerifier>();
    std::shared_ptr<TableVerifier> codegen_P_C_A = std::make_shared<TableVerifier>();
    codegen_P_C_A->documentations.push_back({"Ca",new IntVerifier,Optional::No,""});
    std::shared_ptr<StringInListVerifier> codegen_P_C_T = std::make_shared<StringInListVerifier>(std::vector<std::string>{"Type7","Type8"});
    codegen_P_C->documentations.push_back({"A",codegen_P_C_A,Optional::No,""});
    codegen_P_C->documentations.push_back({"T",codegen_P_C_T,Optional::No,""});
    codegen_P->documentations.push_back({"A",codegen_P_A,Optional::No,""});
    codegen_P->documentations.push_back({"B",codegen_P_B,Optional::No,""});
    codegen_P->documentations.push_back({"T",codegen_P_T,Optional::No,""});
    codegen_P->documentations.push_back({"C",codegen_P_C,Optional::No,""});

    openspace::documentation::Documentation d = { "D", std::move(id), std::move(codegen_P->documentations) };
    return d;
}

} // namespace codegen

namespace codegen {
namespace internal { 
template<typename T> void bakeTo(const ghoul::Dictionary&, std::string_view, T*) { static_assert(sizeof(T) == 0); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, int* val) { if (d.hasValue<double>(key)) { *val = static_cast<int>(d.value<double>(key)); } else if (d.hasValue<int>(key)) { *val = d.value<int>(key); } else { throw std::logic_error("Unexpected type"); } }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, P::A::T* val) {
    std::string v = d.value<std::string>(key);
    if (v == "Type1") { *val = P::A::T::Type1; }
    if (v == "Type2") { *val = P::A::T::Type2; }
}
template <> void bakeTo<P::A>(const ghoul::Dictionary& d, std::string_view key, P::A* val) {
    P::A& res = *val;
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    internal::bakeTo(dict, "T", &res.t);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, P::B::T* val) {
    std::string v = d.value<std::string>(key);
    if (v == "Type3") { *val = P::B::T::Type3; }
    if (v == "Type4") { *val = P::B::T::Type4; }
}
template <> void bakeTo<P::B>(const ghoul::Dictionary& d, std::string_view key, P::B* val) {
    P::B& res = *val;
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    internal::bakeTo(dict, "T", &res.t);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, P::T* val) {
    std::string v = d.value<std::string>(key);
    if (v == "Type5") { *val = P::T::Type5; }
    if (v == "Type6") { *val = P::T::Type6; }
}
template <> void bakeTo<P::C::A>(const ghoul::Dictionary& d, std::string_view key, P::C::A* val) {
    P::C::A& res = *val;
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    internal::bakeTo(dict, "Ca", &res.ca);
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, P::C::T* val) {
    std::string v = d.value<std::string>(key);
    if (v == "Type7") { *val = P::C::T::Type7; }
    if (v == "Type8") { *val = P::C::T::Type8; }
}
template <> void bakeTo<P::C>(const ghoul::Dictionary& d, std::string_view key, P::C* val) {
    P::C& res = *val;
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    internal::bakeTo(dict, "A", &res.a);
    internal::bakeTo(dict, "T", &res.t);
}

} // namespace internal

template <typename T> T bake(const ghoul::Dictionary&) { static_assert(sizeof(T) == 0); }

template <> P bake<P>(const ghoul::Dictionary& dict) {
    openspace::documentation::testSpecificationAndThrow(codegen::doc<P>("P"), dict, "D");
    P res;
    internal::bakeTo(dict, "A", &res.a);
    internal::bakeTo(dict, "B", &res.b);
    internal::bakeTo(dict, "T", &res.t);
    internal::bakeTo(dict, "C", &res.c);
    return res;
}

}// namespace codegen
