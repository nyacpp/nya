cmake_minimum_required(VERSION 3.9)
project(nya)


add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE src)
