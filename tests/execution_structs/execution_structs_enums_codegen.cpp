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
    std::shared_ptr<StringInListVerifier> codegen_Parameters_A = std::make_shared<StringInListVerifier>(std::vector<std::string>{"Value1","value2","Value3"});
    std::shared_ptr<StringInListVerifier> codegen_Parameters_B = std::make_shared<StringInListVerifier>(std::vector<std::string>{"Value1","value2","Value3"});
    std::shared_ptr<StringInListVerifier> codegen_Parameters_C = std::make_shared<StringInListVerifier>(std::vector<std::string>{"Value1","value2","Value3"});
    std::shared_ptr<StringInListVerifier> codegen_Parameters_D = std::make_shared<StringInListVerifier>(std::vector<std::string>{"On a second line or else one line would be too long","ValueB","a continuation line as the last element of the enum"});
    codegen_Parameters->documentations.push_back({"EnumAValue",codegen_Parameters_A,Optional::No,"variable enumAValue documentation"});
    codegen_Parameters->documentations.push_back({"EnumBValue",codegen_Parameters_B,Optional::Yes,"variable enumBValue documentation"});
    codegen_Parameters->documentations.push_back({"EnumCValue",new TableVerifier({{"*",codegen_Parameters_C,Optional::Yes, "enum C documentation"}})
,Optional::No,"variable enumCValue documentation"});
    codegen_Parameters->documentations.push_back({"EnumDValue",codegen_Parameters_D,Optional::No,"variable enumDValue documentation"});

    openspace::documentation::Documentation d = { "Enums", std::move(id), std::move(codegen_Parameters->documentations) };
    return d;
}

} // namespace codegen

namespace codegen {
namespace internal { 
template<typename T> void bakeTo(const ghoul::Dictionary&, std::string_view, T*) { static_assert(sizeof(T) == 0); }
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val);
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val);
void bakeTo(const ghoul::Dictionary& d, std::string_view key, Parameters::A* val) {
    std::string v = d.value<std::string>(key);
    if (v == "Value1") { *val = Parameters::A::Value1; }
    if (v == "value2") { *val = Parameters::A::value2; }
    if (v == "Value3") { *val = Parameters::A::Value3; }
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, Parameters::B* val) {
    std::string v = d.value<std::string>(key);
    if (v == "Value1") { *val = Parameters::B::Value1; }
    if (v == "value2") { *val = Parameters::B::value2; }
    if (v == "Value3") { *val = Parameters::B::Value3; }
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, Parameters::C* val) {
    std::string v = d.value<std::string>(key);
    if (v == "Value1") { *val = Parameters::C::Value1; }
    if (v == "value2") { *val = Parameters::C::value2; }
    if (v == "Value3") { *val = Parameters::C::Value3; }
}
void bakeTo(const ghoul::Dictionary& d, std::string_view key, Parameters::D* val) {
    std::string v = d.value<std::string>(key);
    if (v == "On a second line or else one line would be too long") { *val = Parameters::D::VeryLongValueThatIsSoLongWithAnEvenLongerKeyWhichNeedsToBe; }
    if (v == "ValueB") { *val = Parameters::D::ValueB; }
    if (v == "a continuation line as the last element of the enum") { *val = Parameters::D::SecondVeryLongValueThatWillCheckIfWeDetectPropertyThatWeHave; }
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
    openspace::documentation::testSpecificationAndThrow(codegen::doc<Parameters>("Parameters"), dict, "Enums");
    Parameters res;
    internal::bakeTo(dict, "EnumAValue", &res.enumAValue);
    internal::bakeTo(dict, "EnumBValue", &res.enumBValue);
    internal::bakeTo(dict, "EnumCValue", &res.enumCValue);
    internal::bakeTo(dict, "EnumDValue", &res.enumDValue);
    return res;
}

}// namespace codegen