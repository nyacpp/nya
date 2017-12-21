#ifndef ENUMNYA_HPP
#define ENUMNYA_HPP

/*
// If you want enum with string conversions:
enum class MyEnum
{
	One,
	Two = 20,
	Three,     // It's the third
	Four = 40, // It's the fourth
};

// Write something like this:
#define MyEnumDef(K, V)                 \
	K(One)                              \
	V(Two, 20)                          \
	K(Three)    / * It's the third * /  \
	V(Four, 40) / * It's the fourth * /
nya_enum(MyEnum, MyEnumDef)


// enum to string. If wrong, return "!~MyEnum~"
// ( implemented with usual switch )
MyEnum e1 = MyEnum::One;
cout << e1 << endl;         // 0
cout << e1.c_str() << endl; // "One"

// string to enum. If wrong, return -1
// ( implemented with if-else strcmp )
MyEnum e2 = "Two";
switch (e2)
{
	case MyEnum::One: cout << "-> 1\n"; break;
	case MyEnum::Two: cout << "-> 2\n"; break;
}

CXX_STANDARD 98
*/

#include <cstring>
#include <string>

#define NYA_ENUM_K(KEY) KEY,
#define NYA_ENUM_KV(KEY, VALUE) KEY = VALUE,

#define NYA_ELIF_K(KEY) else if (!strcmp(str, #KEY)) value = KEY;
#define NYA_ELIF_KV(KEY, VALUE) NYA_ELIF_K(KEY)

#define NYA_ELIFS_K(KEY) else if (str == #KEY) value = KEY;
#define NYA_ELIFS_KV(KEY, VALUE) NYA_ELIFS_K(KEY)

#define NYA_CASE_K(KEY) case KEY: return #KEY;
#define NYA_CASE_KV(KEY, VALUE) NYA_CASE_K(KEY)

#define nya_typed_enum(ENUM_NAME, ENUM_DEF, ENUM_TYPE)           \
struct ENUM_NAME                                                 \
{                                                                \
    enum ENUM_NAME##Enum : ENUM_TYPE                             \
    { ENUM_DEF(NYA_ENUM_K, NYA_ENUM_KV) };                       \
                                                                 \
    ENUM_NAME() : value((ENUM_NAME##Enum)-1) {}                  \
    ENUM_NAME(ENUM_NAME##Enum en) : value(en) {}                 \
    ENUM_NAME(ENUM_TYPE n) : value((ENUM_NAME##Enum)n) {}        \
                                                                 \
    ENUM_NAME(const char* str)                                   \
    {                                                            \
        if (!*str) value = (ENUM_NAME##Enum)-1;                  \
        ENUM_DEF(NYA_ELIF_K, NYA_ELIF_KV)                        \
        else value = (ENUM_NAME##Enum)-1;                        \
    }                                                            \
                                                                 \
    ENUM_NAME(const std::string& str)                            \
    {                                                            \
        if (str.empty()) value = (ENUM_NAME##Enum)-1;            \
        ENUM_DEF(NYA_ELIFS_K, NYA_ELIFS_KV)                      \
        else value = (ENUM_NAME##Enum)-1;                        \
    }                                                            \
                                                                 \
    const char* c_str() const                                    \
    {                                                            \
        switch (value)                                           \
        {                                                        \
            ENUM_DEF(NYA_CASE_K, NYA_CASE_KV)                    \
            default: return "!~" #ENUM_NAME "~";                 \
        }                                                        \
    }                                                            \
                                                                 \
    operator ENUM_NAME##Enum() const { return value; }           \
                                                                 \
private:                                                         \
    ENUM_NAME##Enum value;                                       \
};

#define nya_enum(ENUM_NAME, ENUM_DEF) nya_typed_enum(ENUM_NAME, ENUM_DEF, int)

#endif //ENUMNYA_HPP
