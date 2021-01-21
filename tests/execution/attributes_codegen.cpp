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
template <> openspace::documentation::Documentation doc<openspace::Attributes>() {
    using namespace openspace::documentation;
    TableVerifier* codegen_Parameters = new TableVerifier;
    codegen_Parameters->documentations.push_back({"KeyKey",new DoubleVerifier,Optional::No,"keyValue documentation"});
    codegen_Parameters->documentations.push_back({"KeyKeyOptional",new DoubleVerifier,Optional::Yes,"keyValueOptional documentation"});
    codegen_Parameters->documentations.push_back({"InRangeValueInt",new InRangeVerifier<IntVerifier>(-2, 2),Optional::No,"inRangeValueInt documentation"});
    codegen_Parameters->documentations.push_back({"InRangeValueIntOptional",new InRangeVerifier<IntVerifier>(-2, 2),Optional::Yes,"inRangeValueIntOptional documentation"});
    codegen_Parameters->documentations.push_back({"InRangeValueFloat",new InRangeVerifier<DoubleVerifier>(-0.5, 0.75),Optional::No,"inRangeValueFloat documentation"});
    codegen_Parameters->documentations.push_back({"InRangeValueFloatOptional",new InRangeVerifier<DoubleVerifier>(-0.5, 0.75),Optional::Yes,"inRangeValueFloatOptional documentation"});
    codegen_Parameters->documentations.push_back({"NotInRangeValueInt",new NotInRangeVerifier<IntVerifier>(5, 7),Optional::No,"notInRangeValueInt documentation"});
    codegen_Parameters->documentations.push_back({"NotInRangeValueIntOptional",new NotInRangeVerifier<IntVerifier>(5, 7),Optional::Yes,"notInRangeValueIntOptional documentation"});
    codegen_Parameters->documentations.push_back({"NotInRangeValueFloat",new NotInRangeVerifier<DoubleVerifier>(-0.5, 0.5),Optional::No,"notInRangeValueFloat documentation"});
    codegen_Parameters->documentations.push_back({"NotInRangeValueFloatOptional",new NotInRangeVerifier<DoubleVerifier>(-0.5, 0.5),Optional::Yes,"notInRangeValueFloatOptional documentation"});
    codegen_Parameters->documentations.push_back({"LessValueInt",new LessVerifier<IntVerifier>(-5),Optional::No,"lessValueInt documentation"});
    codegen_Parameters->documentations.push_back({"LessValueIntOptional",new LessVerifier<IntVerifier>(-5),Optional::Yes,"lessValueIntOptional documentation"});
    codegen_Parameters->documentations.push_back({"LessValueFloat",new LessVerifier<DoubleVerifier>(15.0),Optional::No,"lessValueFloat documentation"});
    codegen_Parameters->documentations.push_back({"LessValueFloatOptional",new LessVerifier<DoubleVerifier>(15.0),Optional::Yes,"lessValueFloatOptional documentation"});
    codegen_Parameters->documentations.push_back({"LessEqualValueInt",new LessEqualVerifier<IntVerifier>(25),Optional::No,"lessEqualValueInt documentation"});
    codegen_Parameters->documentations.push_back({"LessEqualValueIntOptional",new LessEqualVerifier<IntVerifier>(25),Optional::Yes,"lessEqualValueIntOptional documentation"});
    codegen_Parameters->documentations.push_back({"LessEqualValueFloat",new LessEqualVerifier<DoubleVerifier>(12.0),Optional::No,"lessEqualValueFloat documentation"});
    codegen_Parameters->documentations.push_back({"LessEqualValueFloatOptional",new LessEqualVerifier<DoubleVerifier>(12.0),Optional::Yes,"lessEqualValueFloatOptional documentation"});
    codegen_Parameters->documentations.push_back({"GreaterValueInt",new GreaterVerifier<IntVerifier>(45),Optional::No,"greaterValueInt documentation"});
    codegen_Parameters->documentations.push_back({"GreaterValueIntOptional",new GreaterVerifier<IntVerifier>(45),Optional::Yes,"greaterValueIntOptional documentation"});
    codegen_Parameters->documentations.push_back({"GreaterValueFloat",new GreaterVerifier<DoubleVerifier>(-5.0),Optional::No,"greaterValueFloat documentation"});
    codegen_Parameters->documentations.push_back({"GreaterValueFloatOptional",new GreaterVerifier<DoubleVerifier>(-5.0),Optional::Yes,"greaterValueFloatOptional documentation"});
    codegen_Parameters->documentations.push_back({"GreaterEqualValueInt",new GreaterEqualVerifier<IntVerifier>(2),Optional::No,"greaterEqualValueInt documentation"});
    codegen_Parameters->documentations.push_back({"GreaterEqualValueIntOptional",new GreaterEqualVerifier<IntVerifier>(2),Optional::Yes,"greaterEqualValueIntOptional documentation"});
    codegen_Parameters->documentations.push_back({"GreaterEqualValueFloat",new GreaterEqualVerifier<DoubleVerifier>(-25.0),Optional::No,"greaterEqualValueFloat documentation"});
    codegen_Parameters->documentations.push_back({"GreaterEqualValueFloatOptional",new GreaterEqualVerifier<DoubleVerifier>(-25.0),Optional::Yes,"greaterEqualValueFloatOptional documentation"});
    codegen_Parameters->documentations.push_back({"UnequalValueInt",new UnequalVerifier<IntVerifier>(1),Optional::No,"unequalValueInt documentation"});
    codegen_Parameters->documentations.push_back({"UnequalValueIntOptional",new UnequalVerifier<IntVerifier>(1),Optional::Yes,"unequalValueIntOptional documentation"});
    codegen_Parameters->documentations.push_back({"UnequalValueFloat",new UnequalVerifier<DoubleVerifier>(123.0),Optional::No,"unequalValueFloat documentation"});
    codegen_Parameters->documentations.push_back({"UnequalValueFloatOptional",new UnequalVerifier<DoubleVerifier>(123.0),Optional::Yes,"unequalValueFloatOptional documentation"});
    codegen_Parameters->documentations.push_back({"DescValue",new BoolVerifier,Optional::No,desc.description});
    codegen_Parameters->documentations.push_back({"InListValue1",new InListVerifier<StringVerifier>({"A", "B", "C"}),Optional::No,"inListValue1 documentation"});
    codegen_Parameters->documentations.push_back({"InListValue1Optional",new InListVerifier<StringVerifier>({"A", "B", "C"}),Optional::Yes,"inListValue1Optional documentation"});
    codegen_Parameters->documentations.push_back({"InListValue2",new InListVerifier<StringVerifier>({List}),Optional::No,"inListValue2 documentation"});
    codegen_Parameters->documentations.push_back({"InListValue2Optional",new InListVerifier<StringVerifier>({List}),Optional::Yes,"inListValue2Optional documentation"});
    codegen_Parameters->documentations.push_back({"UnequalValueString",new UnequalVerifier<StringVerifier>("abcdef"),Optional::No,"unequalValueString documentation"});
    codegen_Parameters->documentations.push_back({"UnequalValueStringOptional",new UnequalVerifier<StringVerifier>("abcdef"),Optional::Yes,"unequalValueStringOptional documentation"});
    codegen_Parameters->documentations.push_back({"ReferenceValue",new ReferencingVerifier("abc"),Optional::Yes,"referenceValue documentation"});

    openspace::documentation::Documentation d = { "Attributes", "Attributes", std::move(codegen_Parameters->documentations) };
    delete codegen_Parameters;
    return d;
}
} // namespace codegen


namespace codegen {
namespace internal {
template<typename T> void bakeTo(const ghoul::Dictionary&, std::string_view, T*) { static_assert(sizeof(T) == 0); } // This should never be called
void bakeTo(const ghoul::Dictionary& d, std::string_view key, bool* val) { *val = d.value<bool>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, float* val) { *val = static_cast<float>(d.value<double>(key)); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, int* val) { *val = static_cast<int>(d.value<double>(key)); }
void bakeTo(const ghoul::Dictionary&, std::string_view, std::monostate* val) { *val = std::monostate(); }
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val);
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::string* val) { *val = d.value<std::string>(key); }

template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val) {
    if (d.hasKey(key)) {
        T v;
        bakeTo(d, key, &v);
        *val = v;
    }
    else *val = std::nullopt;
}

} // namespace internal

template <typename T> T bake(const ghoul::Dictionary&) { static_assert(sizeof(T) == 0); }
template <> Parameters bake<Parameters>(const ghoul::Dictionary& dict) {
    openspace::documentation::testSpecificationAndThrow(codegen::doc<openspace::Attributes>(), dict, "Attributes");
    Parameters res;
    internal::bakeTo(dict, "KeyKey", &res.keyValue);
    internal::bakeTo(dict, "KeyKeyOptional", &res.keyValueOptional);
    internal::bakeTo(dict, "InRangeValueInt", &res.inRangeValueInt);
    internal::bakeTo(dict, "InRangeValueIntOptional", &res.inRangeValueIntOptional);
    internal::bakeTo(dict, "InRangeValueFloat", &res.inRangeValueFloat);
    internal::bakeTo(dict, "InRangeValueFloatOptional", &res.inRangeValueFloatOptional);
    internal::bakeTo(dict, "NotInRangeValueInt", &res.notInRangeValueInt);
    internal::bakeTo(dict, "NotInRangeValueIntOptional", &res.notInRangeValueIntOptional);
    internal::bakeTo(dict, "NotInRangeValueFloat", &res.notInRangeValueFloat);
    internal::bakeTo(dict, "NotInRangeValueFloatOptional", &res.notInRangeValueFloatOptional);
    internal::bakeTo(dict, "LessValueInt", &res.lessValueInt);
    internal::bakeTo(dict, "LessValueIntOptional", &res.lessValueIntOptional);
    internal::bakeTo(dict, "LessValueFloat", &res.lessValueFloat);
    internal::bakeTo(dict, "LessValueFloatOptional", &res.lessValueFloatOptional);
    internal::bakeTo(dict, "LessEqualValueInt", &res.lessEqualValueInt);
    internal::bakeTo(dict, "LessEqualValueIntOptional", &res.lessEqualValueIntOptional);
    internal::bakeTo(dict, "LessEqualValueFloat", &res.lessEqualValueFloat);
    internal::bakeTo(dict, "LessEqualValueFloatOptional", &res.lessEqualValueFloatOptional);
    internal::bakeTo(dict, "GreaterValueInt", &res.greaterValueInt);
    internal::bakeTo(dict, "GreaterValueIntOptional", &res.greaterValueIntOptional);
    internal::bakeTo(dict, "GreaterValueFloat", &res.greaterValueFloat);
    internal::bakeTo(dict, "GreaterValueFloatOptional", &res.greaterValueFloatOptional);
    internal::bakeTo(dict, "GreaterEqualValueInt", &res.greaterEqualValueInt);
    internal::bakeTo(dict, "GreaterEqualValueIntOptional", &res.greaterEqualValueIntOptional);
    internal::bakeTo(dict, "GreaterEqualValueFloat", &res.greaterEqualValueFloat);
    internal::bakeTo(dict, "GreaterEqualValueFloatOptional", &res.greaterEqualValueFloatOptional);
    internal::bakeTo(dict, "UnequalValueInt", &res.unequalValueInt);
    internal::bakeTo(dict, "UnequalValueIntOptional", &res.unequalValueIntOptional);
    internal::bakeTo(dict, "UnequalValueFloat", &res.unequalValueFloat);
    internal::bakeTo(dict, "UnequalValueFloatOptional", &res.unequalValueFloatOptional);
    internal::bakeTo(dict, "DescValue", &res.descValue);
    internal::bakeTo(dict, "InListValue1", &res.inListValue1);
    internal::bakeTo(dict, "InListValue1Optional", &res.inListValue1Optional);
    internal::bakeTo(dict, "InListValue2", &res.inListValue2);
    internal::bakeTo(dict, "InListValue2Optional", &res.inListValue2Optional);
    internal::bakeTo(dict, "UnequalValueString", &res.unequalValueString);
    internal::bakeTo(dict, "UnequalValueStringOptional", &res.unequalValueStringOptional);
    internal::bakeTo(dict, "ReferenceValue", &res.referenceValue);
    return res;
}
} // namespace codegen
