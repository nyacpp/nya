cmake_minimum_required(VERSION 3.10)
project(nya)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE src)


# tests
if(NYA_TESTS)
    message(STATUS "nya tests enabled")

    set(Boost_USE_STATIC_LIBS ON)
    find_package(Boost REQUIRED system)

    set(TESTS_NAME ${PROJECT_NAME}_tests)
    file(GLOB_RECURSE TEST_SOURCES test/*.cpp test/*.h test/*.hpp)

    add_executable(${TESTS_NAME} EXCLUDE_FROM_ALL ${TEST_SOURCES})
    set_target_properties(${TESTS_NAME} PROPERTIES CXX_STANDARD 17)
    target_include_directories(${TESTS_NAME} PRIVATE ../catch)      # catch
    target_link_libraries(${TESTS_NAME} -static
            ${PROJECT_NAME}
            ${Boost_SYSTEM_LIBRARY})
    if(MINGW)
        target_link_libraries(${TESTS_NAME} ws2_32) # boost::asio
    endif()
endif()