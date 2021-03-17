# Overview
The codegen program created generated code for `struct`s marked with the `[[codegen::Dictionary(Name)]]` attribute, where *Name* is a unique name (mostly the class name of the Renderable for which the code is generated).  Everything touched by the code generation has to be delared inside the struct (referred to as the *root struct*).  Member variables, structs, documentations can be modified by adding attributes of the style `[[codegen::TYPE(PARAMETER)]]` where *TYPE* is a keyword for the attribute and *PARAMETER* are optional parameters that might be necessary. Multiple attributes can be added by separating them with a comma (`[[codegen::key(ABC), codegen::inrange(0.0, 1.0)]]`).

Execution:
`codegen.exe --folder C:/Development/OpenSpace/modules`  to run it an all files recursively in the modules folder.  Every file that does not contain a marked struct will be ignored.  For every other file `renderabletest.cpp`, a `renderabletest_codegen.cpp` will be generated that will have to be included directly *after* the struct definition. For example in a file renderableexample.cpp:
```
struct [[codegen::Dictionary(RenderableExample)]] Params {
  // Description for example
  float example;
};
#include "renderabletest_codegen.cpp"
```

## Root struct
The root struct needs to be marked with the `[[codegen::Dictionary(Name)]]` attribute, where *Name* is a unique name.  Every struct not marked as such will be ignored by the codegen program.  Furthermore, the root struct (and the following include) must be declared in an anonymous namespace.

### Attributes
 - `[[codegen::namespace(NS)]]`: Necessary if the type specified in the `Dictionary` attribute is living in namespace other than `openspace`

## Documentation
All types and variable definitions can have comments defined directly before the struct, or variable.

### Attributes
 - `[[codegen::verbatim(ID.description)]]` will be replaced with `ID.description` to be able to reuse descriptions from a PropertyInfo `ID` or any other parameter.  The only difference to writing `// ID.description` is that the latter will add " around the parameter which `codegen::verbatim` omits

## Supported types for member variables
 - C++ types: `bool`, `int`, `float`, `double`, `std::vector`, `std::optional`, `std::variant`, `std::string`, `std::filesystem::path`
 - `glm::ivec2`, `glm::ivec3`, `glm::ivec4`, `glm::dvec2`, `glm::dvec3`, `glm::dvec4`, `glm::vec2`, `glm::vec3`, `glm::vec4`, `glm::mat2x2`, `glm::mat2x3`, `glm::mat2x4`, `glm::mat3x2`, `glm::mat3x3`, `glm::mat3x4`, `glm::mat4x2`, `glm::mat4x3`, `glm::mat4x4`, `glm::dmat2x2`, `glm::dmat2x3`, `glm::dmat2x4`, `glm::dmat3x2`, `glm::dmat3x3`, `glm::dmat3x4`, `glm::dmat4x2`, `glm::dmat4x3`, `glm::dmat4x4`, `ghoul::Dictionary`
 - `struct`s (must be defined inside the root struct)
 - `enum class` (must be defind inside the root struct)
 - `std::monostate`. In a rare case where you need to reference another documentation generated with a specific ID elsewhere within OpenSpace.  A variable of this attribute *must* be paired with a `[[codegen::reference("Foo")]]` attribute, where `Foo` is the `id` of a defined Documentation that has been registered with the `DocumentationEngine`

The variable's name will be used to get a value out of the dictionary in the baking process.  The only transformation of the name is that the first letter is capitalized (`referenceName` will be looked up as `ReferenceName`).

### Member Attributes
 - `[[codegen::key("Name")]]`:  Use the `Name` instead of the (first letter capitalized) variable name to look up a value in the Dictionary during the baking. This value has to be encapsulated in "" if it is a string literal.  If you want to use the return value of a function, the "" have to be omitted, like `[[codegen::key(unitList())]]`
 - `[[codegen::inrange(min, max)]]`:  Makes sure that the `int`, `float`, or `double` value is between the `min` and `max` values.  Example: `float foo [[codegen::inrange(0.0, 1.0)]];`
 - `[[codegen::notinrange(min, max)]]`:  Makes sure that the `int`, `float`, or `double` value is outside the `min` and `max` values.  Example: `float foo [[codegen::notinrange(0.0, 1.0)]];`
 - `[[codegen::less(val)]]`:  Makes sure that the `int`, `float`, or `double` value is less than the `val` value.  Example: `float foo [[codegen::less(0.0)]];`
 - `[[codegen::lessequal(val)]]`:  Makes sure that the `int`, `float`, or `double` value is less than or equal to the `val` value.  Example: `float foo [[codegen::lessequal(0.0)]];`
 - `[[codegen::greater(val)]]`, `[[codegen:greaterequal(val)]]`, `[[codegen:unequal(val)]]` likewise
 - `[[codegen::inlist("v1", "v2", "v3")]]`:  Checks whether a `std::string` variable is one of a finite list of values.  Example: `std::string foo [[codegen::inlist("v1", "v2", "v3")]];`
 - `[[codegen::notinlist("v1", "v2", "v3")]]`:  Checks whether a `std::string` variable is not one of a finite list of values.  Example: `std::string foo [[codegen::notinlist("v1", "v2", "v3")]];`
 - `[[codegen::annotation(text)]]`:  Adds an annotation decorator to the member.  Currently only supported for `std::string` and it cannot be used together with other attributes.  Example: `std::string foo [[codegen::annotation(Must be a valid bar)]]`
 - `[[codegen::reference("foo")]]`:  Marks a `std::monostate` or `ghoul::Dictionary` as a referencing verifier that will look up a different Documentation elsewhere in the code.  This attribute can only be used with these two types.
 - `[[codegen::color()]]`:  Marks a glm::vec3, glm::vec4, glm::dvec3, or glm::dvec4 as containing a color, meaning that a `ColorVerifier` is generated that checks whether all components are in the range `[0,1]`. The parameter must be either empty, `true`, or `false`
 - `[[codegen::directory()]]`: Marks a `std::filesystem::path` to be allowed to be a directory. The parameter must be either empty, `true`, or `false`

## Enum class
`enum class` value are looked up through string matching against the enum value when baking.  For example:
```
enum class E {
    V1,
    V2,
    V3
};
```
When baking, a Dictionary containing a string "V1" will result in the `E::V1` enum to be selected

### Enum Attributes
 - `[[codegen::key(Name)]]`: Use the "Name" instead of the enum values name


## Verifier Mappings
This is a complete list of variable types and attribute combinations.  We are **not** listing the `[[codegen::key(...)]]` attribute here, as this is allowed with *every* variable.

 - `int` + `[[codegen::inrange]]` -> `InRangeVerifier<IntVerifier>`
 - `int` + `[[codegen::notinrange]]` -> `NotInRangeVerifier<IntVerifier>`
 - `int` + `[[codegen::less]]` -> `LessVerifier<IntVerifier>`
 - `int` + `[[codegen::lessequal]]` -> `LessEqualVerifier<IntVerifier>`
 - `int` + `[[codegen::greater]]` -> `GreaterVerifier<IntVerifier>`
 - `int` + `[[codegen::greaterequal]]` -> `GreaterEqualVerifier<IntVerifier>`
 - `int` + `[[codegen::unequal]]` -> `UnequalVerifier<IntVerifier>`
 - `double` + `[[codegen::inrange]]` -> `InRangeVerifier<DoubleVerifier>`
 - `double` + `[[codegen::notinrange]]` -> `NotInRangeVerifier<DoubleVerifier>`
 - `double` + `[[codegen::less]]` -> `LessVerifier<DoubleVerifier>`
 - `double` + `[[codegen::lessequal]]` -> `LessEqualVerifier<DoubleVerifier>`
 - `double` + `[[codegen::greater]]` -> `GreaterVerifier<DoubleVerifier>`
 - `double` + `[[codegen::greaterequal]]` -> `GreaterEqualVerifier<DoubleVerifier>`
 - `double` + `[[codegen::unequal]]` -> `UnequalVerifier<DoubleVerifier>`
 - `float` + `[[codegen::inrange]]` -> `InRangeVerifier<DoubleVerifier>`
 - `float` + `[[codegen::notinrange]]` -> `NotInRangeVerifier<DoubleVerifier>`
 - `float` + `[[codegen::less]]` -> `LessVerifier<DoubleVerifier>`
 - `float` + `[[codegen::lessequal]]` -> `LessEqualVerifier<DoubleVerifier>`
 - `float` + `[[codegen::greater]]` -> `GreaterVerifier<DoubleVerifier>`
 - `float` + `[[codegen::greaterequal]]` -> `GreaterEqualVerifier<DoubleVerifier>`
 - `float` + `[[codegen::unequal]]` -> `UnequalVerifier<DoubleVerifier>`
 - `std::string` + `[[codegen::inlist]]` -> `InListVerifier<StringVerifier>`
 - `std::string` + `[[codegen::unequal]]` -> `UnequalVerifier<StringVerifier>`
 - `std::string` + `[[codegen::annotation]]` -> `AnnotationVerifier<StringVerifier>`
 - `glm::vec3` + `[[codegen::color]]` -> `Color3Verifier`
 - `glm::vec4` + `[[codegen::color]]` -> `Color4Verifier`
 - `glm::dvec3` + `[[codegen::color]]` -> `Color3Verifier`
 - `glm::dvec4` + `[[codegen::color]]` -> `Color4Verifier`
 - `std::filesystem::path` + `[[codegen::directory()]]` -> `DirectoryVerifier`
 - `ghoul::Dictionary` + `[[codegen::reference()]]` -> `ReferencingVerifier`
