# NYA Library
*[nya.hpp](src/nya.hpp) is C++ header only library containing some useful aliases.*
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


The library is free to use — either fork or just copy the file.
```c++
#include <nya.hpp>
```


-----------------------------------------------------------------

## Additional C++ fun
* *[enum](src/nya/enum.hpp) with conversion to and from string*
```c++
#define MyEnumDef(K, V)                 \
    K(One)                              \
    V(Two, 20)                          \
    K(Three)    /* It's the third */    \
    V(Four, 40) /* It's the fourth */
nya_enum(MyEnum, MyEnumDef)

MyEnum e1 = MyEnum::One;
const char* s = e1.c_str();  // to string
MyEnum e2 = "Two";           // from string
switch (e2)                  // switch
{
    case MyEnum::One: cout << "-> 1\n"; break;
    case MyEnum::Two: cout << "-> 2\n"; break;
}
```

* *[exception](src/nya/exception.hpp) with file:line*
```c++
nya_throw << "File %s is not found"s % fileName;
```

* *[format](src/nya/format.hpp) — boost::format wrapper*
```c++
cout << "Alpha %s Gamma"s % "Beta"; // "Alpha Beta Gamma"
```

* *[io](src/nya/io.hpp) notes*
```c++
cout << SomeClass(); // any class with string cast operator
cout << std::variant<int, float>(1); // variant streaming is not in std yet
```

* *cozy [log](src/nya/log.hpp)*
```c++
error_log << "Number %d shouldn't be here"s % 5;
```

* *[signal](src/nya/signal.hpp) — boost signal-slot and event loop wrapper*
```c++
nya::sig<void(int)> foo;           // signal
void bar(int y) { x1 = y; }        // slot 1
auto baz = [](int y) { x2 = y; };  // slot 2

{
    nya::event_loop eventLoop;
    nya::connect_in(eventLoop, foo, bar);      // async connect to function
    nya::connect_in(eventLoop, foo, baz);      // async connect to lambda
  
    auto w = make_u<nya::event_loop::work>(eventLoop);
    thread th([&eventLoop] { eventLoop.run(); });
    
    foo(5); // call slots in "th" thread
    
    w.reset();
    th.join();
}
```

## Frequently used headers
Frequently used headers are gathered in [api](src/nya/api.hpp):
```c++
#include <nya/api.hpp>
```
