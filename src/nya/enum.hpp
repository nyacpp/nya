#ifndef ENUMNYA_HPP
#define ENUMNYA_HPP

/*
// If you want enum with string conversions:
enum MyEnum
{
	One,
	Two = 20,
	Three,     // It's the third one
	Four = 40, // It's the fourth one
	Five,
	Six
};

// Write something like this:
#define MyEnumDef(K, V) \
	K(One) \
	V(Two, 20) \
	K(Three,    "It's the third") \
	V(Four, 40, "It's the fourth")
NYA_ENUM(MyEnum, MyEnumDef)


// Getting string. If wrong, return "!~MyEnum~"
// ( implemented with usual switch )
const char* s = etos(One);

// Getting number. If wrong, return -1
// ( implemented with static unordered_map )
MyEnum e1 = stoe("One");
MyEnum e2 = stoe("Two");
MyEnum e3 = stoe("Three");


// Waiting for c++20 __VA_OPT__ to use enum class...
// For lower versions namespace around enum can help a bit.
*/

#if __cplusplus >= 201103L
#include <unordered_map>
#include <string>

#if __cplusplus >= 201703L
#define _prefix_enumnya [[maybe_unused]] static
#else
#define _prefix_enumnya template<typename ...>
#endif

#define NYA_ENUM_K(KEY, ...) KEY,
#define NYA_ENUM_KV(KEY, VALUE, ...) KEY = VALUE,
#define NYA_CASE_K(KEY, ...) case KEY: return #KEY;
#define NYA_MAP_K(KEY, ...) { #KEY, KEY },

#define NYA_ENUM(ENUM_NAME, ENUM_DEF) \
	enum ENUM_NAME { ENUM_DEF(NYA_ENUM_K, NYA_ENUM_KV) }; \
	\
	_prefix_enumnya const char* etos(ENUM_NAME e) \
	{ switch( e ) { ENUM_DEF(NYA_CASE_K, NYA_CASE_K) default: return "!~" #ENUM_NAME "~"; } } \
	\
	_prefix_enumnya ENUM_NAME stoe(const char* s) \
	{ static std::unordered_map<std::string, ENUM_NAME> m = { ENUM_DEF(NYA_MAP_K, NYA_MAP_K) }; \
	  auto it = m.find(s); if( it != m.end() ) return it->second; return (ENUM_NAME)-1; }
	
#else // C or C++03
// Only enums with comments provided by default! Use NYA_ENUM4 for full syntax.
// It'll cause warnings. You can supress them with -Wno-unused-function
// stoe() is not defined.
// Maybe you'll need some undefs, because scope is global: #undef One

#define NYA_ENUM_K(KEY) KEY,
#define NYA_ENUM_KV(KEY, VALUE) KEY = VALUE,
#define NYA_ENUM_KC(KEY, COMMENT) NYA_ENUM_K(KEY)
#define NYA_ENUM_KVC(KEY, VALUE, COMMENT) NYA_ENUM_KV(KEY, VALUE)

#define NYA_CASE_K(KEY) case KEY: return #KEY;
#define NYA_CASE_K1(KEY, VALUE_COMMENT) NYA_CASE_K(KEY)
#define NYA_CASE_KVC(KEY, VALUE, COMMENT) NYA_CASE_K(KEY)

#define NYA_ENUM(ENUM_NAME, ENUM_DEF) \
	enum ENUM_NAME { ENUM_DEF(NYA_ENUM_KC, NYA_ENUM_KVC) }; \
	\
	static const char* etos(ENUM_NAME e) \
	{  switch( e ) { ENUM_DEF(NYA_CASE_K1, NYA_CASE_KVC) default: return "!~" #ENUM_NAME "~"; } }

#define NYA_ENUM4(ENUM_NAME, ENUM_DEF) \
	enum ENUM_NAME { ENUM_DEF(NYA_ENUM_K, NYA_ENUM_KV, NYA_ENUM_KC, NYA_ENUM_KVC) }; \
	\
	static const char* etos(ENUM_NAME e) \
	{  switch( e ) { ENUM_DEF(NYA_CASE_K, NYA_CASE_K1, NYA_CASE_K1, NYA_CASE_KVC) default: return "!~" #ENUM_NAME "~"; } }

#endif // __cplusplus >= 201103L

#endif //ENUMNYA_HPP
