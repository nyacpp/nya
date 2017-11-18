# NYA Library
*It is C++ header only library containing some useful aliases.*
```c++
#define umap std::unordered_map
#define uset std::unordered_set

#define u_p std::unique_ptr
#define s_p std::shared_ptr

#define all_(x) (x).begin(), (x).end()

typedef unsigned int uint;
typedef long long llong;

// and some more ...
```
See [nya.hpp](src/nya.hpp) for details.

The library is free to use — either fork or just copy the file.

## Additional C++ fun
* *[enum](src/nya/enum.hpp) with conversion to and from string*
```c++
#define MyEnumDef(K, V) \
	K(One) \
	V(Two, 20) \
	K(Three,    "It's the third") \
	V(Four, 40, "It's the fourth")
NYA_ENUM(MyEnum, MyEnumDef)

const char* s = etos(One); // to string
MyEnum e1 = stoe("One");   // from string
```

* *[exception](src/nya/exception.hpp) with file:line*
```c++
throw_nya << "File %s is not found"s % fileName;
```

* *[format](src/nya/format.hpp) — boost::format wrapper*
```c++
cout << "abc %s ghi"s % "def"; // abc def ghi
```

* *[io](src/nya/io.hpp) notes*
```c++
ios::sync_with_stdio(false);
cin.tie(0);
```

* *cozy [log](src/nya/log.hpp)*
```c++
error_log << "Number %d shouldn't be here"s % 5;
```

* *[switch](src/nya/switch.hpp) for string (and other types)*
```c++
caseS( "one" )
{
	std::cout << "!\n";
}
case_( "two" )
{
	std::cout << "!!\n";
}
case_( "three" )
{
	std::cout << "!!!\n";
}
switchD( s ) // default
{
	std::cout << "Non-non\n";
}
// or
switch_( s ) // without default
```
