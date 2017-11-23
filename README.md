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
#define MyEnumDef(K, V)               \
  K(One)                              \
  V(Two, 20)                          \
  K(Three)    / * It's the third * /  \
  V(Four, 40) / * It's the fourth * /
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

* *[signal](src/nya/signal.hpp) boost signal-slot and event loop wrapper*
```c++
nya::sig<void(int)> foo;   // signal
void bar(int) {}           // slot
nya::event_loop eventLoop; //
u_p<thread> th;            // thread for eventLoop

// ...
{
    nya::connect_in(eventLoop, foo, bar); // async connect
    
    nya::event_loop::work(eventLoop);
    th.reset(new thread([] { eventLoop.run(); }));
    
    foo(); // call bar in "th" thread
}
```

## Frequently used headers
Frequently used headers are gathered in [api](src/nya/api.hpp):
```c++
#include <nya/api.hpp>
```
