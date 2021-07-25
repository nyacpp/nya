# os specific
if (APPLE)
	set(OS_BUNDLE MACOSX_BUNDLE)
elseif (WIN32)
	include(${CMAKE_CURRENT_LIST_DIR}/windows.cmake)
endif ()

# general
add_definitions(-DWIN32_LEAN_AND_MEAN)                  # for boost::asio - reduces windows.h
add_definitions(-D_USE_MATH_DEFINES)                    # math constants like M_PI

# boost
add_definitions(-DBOOST_ALLOW_DEPRECATED_HEADERS)       # suppress internal boost warnings
add_definitions(-DBOOST_MOVE_USE_STANDARD_LIBRARY_MOVE) # std::move and boost::move won't interfere

# easylogging
set(build_static_lib ON CACHE BOOL "Build easyloggingpp as a static library" FORCE)
add_definitions(-DELPP_NO_DEFAULT_LOG_FILE)             # custom log file
add_definitions(-DELPP_WINSOCK2)                        # for boost::asio
add_definitions(-DELPP_STL_LOGGING)                     # stl
add_definitions(-DELPP_LOG_STD_ARRAY)                   #
add_definitions(-DELPP_LOG_UNORDERED_MAP)               #
add_definitions(-DELPP_LOG_UNORDERED_SET)               #
add_definitions(-DELPP_THREAD_SAFE)                     # thread name

