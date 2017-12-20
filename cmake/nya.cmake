set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# msvc
if(MSVC)
    add_compile_options("/std:c++latest")
endif(MSVC)

# definitions
add_definitions(-DBOOST_MOVE_USE_STANDARD_LIBRARY_MOVE) # std::move and boost::move won't interfere
add_definitions(-DWIN32_LEAN_AND_MEAN)                  # for boost::asio - reduces windows.h

# easylogging
set(build_static_lib ON cache)
add_definitions(-DELPP_NO_DEFAULT_LOG_FILE)             # custom log file
add_definitions(-DELPP_WINSOCK2)                        # for boost::asio
add_definitions(-DELPP_STL_LOGGING)                     # stl
add_definitions(-DELPP_LOG_STD_ARRAY)                   #
add_definitions(-DELPP_LOG_UNORDERED_MAP)               #
add_definitions(-DELPP_LOG_UNORDERED_SET)               #
add_definitions(-DELPP_THREAD_SAFE)                     # thread name
