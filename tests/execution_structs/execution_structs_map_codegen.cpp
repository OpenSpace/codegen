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
    codegen_Parameters->documentations.push_back({"SimpleMap",new TableVerifier({{"*", new StringVerifier, Optional::No }})
,Optional::No,"simpleMap documentation"});
    codegen_Parameters->documentations.push_back({"OptionalMap",new TableVerifier({{"*", new StringVerifier, Optional::No }})
,Optional::Yes,"optionalMap documentation"});
    codegen_Parameters->documentations.push_back({"VectorMap",new TableVerifier({{"*",new TableVerifier({{"*", new StringVerifier, Optional::No }})
,Optional::Yes, }})
,Optional::No,"vectorMap documentation"});
    codegen_Parameters->documentations.push_back({"OptionalVectorMap",new TableVerifier({{"*",new TableVerifier({{"*", new StringVerifier, Optional::No }})
,Optional::Yes, }})
,Optional::Yes,"optionalVectorMap documentation"});
    codegen_Parameters->documentations.push_back({"DictMap",new TableVerifier({{"*", new TableVerifier, Optional::No }})
,Optional::No,"dictMap documentation"});
    codegen_Parameters->documentations.push_back({"OptionalDictMap",new TableVerifier({{"*", new TableVerifier, Optional::No }})
,Optional::Yes,"optionalDictMap documentation"});
    codegen_Parameters->documentations.push_back({"VectorDictMap",new TableVerifier({{"*",new TableVerifier({{"*", new TableVerifier, Optional::No }})
,Optional::Yes, }})
,Optional::No,"vectorDictMap documentation"});
    codegen_Parameters->documentations.push_back({"OptionalVectorDictMap",new TableVerifier({{"*",new TableVerifier({{"*", new TableVerifier, Optional::No }})
,Optional::Yes, }})
,Optional::Yes,"optionalVectorDictMap documentation"});

    openspace::documentation::Documentation d = { "Map", std::move(id), std::move(codegen_Parameters->documentations) };
    return d;
}

} // namespace codegen

namespace codegen {
namespace internal { 
template<typename T> void bakeTo(const ghoul::Dictionary&, std::string_view, T*) { static_assert(sizeof(T) == 0); }
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::optional<T>* val);
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::vector<T>* val);
template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::map<std::string, T>* val);
void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::string* val) { *val = d.value<std::string>(key); }
void bakeTo(const ghoul::Dictionary& d, std::string_view key, ghoul::Dictionary* val) { *val = d.value<ghoul::Dictionary>(key); }

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

template<typename T> void bakeTo(const ghoul::Dictionary& d, std::string_view key, std::map<std::string, T>* val) {
    ghoul::Dictionary dict = d.value<ghoul::Dictionary>(key);
    
    for (std::string_view k : dict.keys()) {
        T v;
        bakeTo(dict, k, &v);
        val->insert({ std::string(k), v });
    }
}

} // namespace internal

template <typename T> T bake(const ghoul::Dictionary&) { static_assert(sizeof(T) == 0); }

template <> Parameters bake<Parameters>(const ghoul::Dictionary& dict) {
    openspace::documentation::testSpecificationAndThrow(codegen::doc<Parameters>("Parameters"), dict, "Map");
    Parameters res;
    internal::bakeTo(dict, "SimpleMap", &res.simpleMap);
    internal::bakeTo(dict, "OptionalMap", &res.optionalMap);
    internal::bakeTo(dict, "VectorMap", &res.vectorMap);
    internal::bakeTo(dict, "OptionalVectorMap", &res.optionalVectorMap);
    internal::bakeTo(dict, "DictMap", &res.dictMap);
    internal::bakeTo(dict, "OptionalDictMap", &res.optionalDictMap);
    internal::bakeTo(dict, "VectorDictMap", &res.vectorDictMap);
    internal::bakeTo(dict, "OptionalVectorDictMap", &res.optionalVectorDictMap);
    return res;
}

}// namespace codegen
