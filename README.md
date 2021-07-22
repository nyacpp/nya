# NYA Library
C++ header only library with a bunch of tricks.

## Usage
```c++
#include <nya.hpp>
//
    uint x;   // unsigned int
    llong y;  // long long
	    
    u_p<MyClass> myObject;    // std::unique_ptr
    s_p<MyClass> myObject;    // std::shared_ptr

    int sum = std::accumulate(nya_all(v), 0);  // begin, end
```

* *see [nya.hpp](src/nya.hpp) for more aliases*


-----------------------------------------------------------------

## Additional C++ Fun
```c++
#include <nya/api.hpp>
```

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

-----------------------------------------------------------------

## Additional CMake Fun

* [submodule](cmake/submodule.cmake) — automatic submodule update (copy the file, if nya is submodule itself)
```cmake
include(nya/cmake/submodule.cmake)
nya_submodule(deps/my_module)
```

* [fetch_content](cmake/fetch_content.cmake) — convenient way to call FetchContent
```cmake
include(nya/cmake/fetch_content.cmake)
nya_fetch_content(https://github.com/catchorg/Catch2.git master)
```
