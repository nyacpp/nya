# definitions
add_definitions(-DBOOST_MOVE_USE_STANDARD_LIBRARY_MOVE) # std::move and boost::move won't interfere
add_definitions(-DWIN32_LEAN_AND_MEAN)                  # for boost::asio - reduces windows.h
add_definitions(-D_USE_MATH_DEFINES)                    # math constants like M_PI

# easylogging
set(build_static_lib ON CACHE BOOL "Build easyloggingpp as a static library" FORCE)
add_definitions(-DELPP_NO_DEFAULT_LOG_FILE)             # custom log file
add_definitions(-DELPP_WINSOCK2)                        # for boost::asio
add_definitions(-DELPP_STL_LOGGING)                     # stl
add_definitions(-DELPP_LOG_STD_ARRAY)                   #
add_definitions(-DELPP_LOG_UNORDERED_MAP)               #
add_definitions(-DELPP_LOG_UNORDERED_SET)               #
add_definitions(-DELPP_THREAD_SAFE)                     # thread name

# gui application setting
if(APPLE)
    set(OS_BUNDLE MACOSX_BUNDLE)
elseif(WIN32)
    set(OS_BUNDLE WIN32)
endif()

# FetchContent into ../folder_name
# nya_fetch(<url> <tag> <folder_name>)
macro(nya_fetch)
    if(NOT ${ARGC} EQUAL 0)
        if(${ARGC} GREATER 1)
            set(FETCH_TAG ${ARGV1})
        else()
            set(FETCH_TAG master)
        endif()

        if(${ARGC} GREATER 2)
            set(FETCH_NAME ${ARGV2})
        else()
            get_filename_component(FETCH_NAME ${ARGV0} NAME_WE)
        endif()

        get_filename_component(FETCH_ROOT ${CMAKE_SOURCE_DIR}/../${FETCH_NAME}  ABSOLUTE)
        get_filename_component(BINARY_DIR_NAME ${CMAKE_BINARY_DIR} NAME)

        message("++ fetch: " ${FETCH_ROOT})

        FetchContent_Declare(${FETCH_NAME}
                GIT_REPOSITORY ${ARGV0}
                GIT_TAG        ${FETCH_TAG}
                SOURCE_DIR     ${FETCH_ROOT}
                BINARY_DIR     ${FETCH_ROOT}/${BINARY_DIR_NAME}
                )
        FetchContent_MakeAvailable(${FETCH_NAME})
    endif()
endmacro(nya_fetch)
