cmake_minimum_required(VERSION 3.11)
project(nya)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE src)

# tests
if(NYA_TESTS)
    add_subdirectory(test)
endif()
