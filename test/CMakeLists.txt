message(STATUS "nya tests enabled")

include(../cmake/nya.cmake)
include(../cmake/fetch_content.cmake)

nya_fetch_content(https://github.com/catchorg/Catch2.git v2.13.6)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.65 REQUIRED system)


set(TESTS_NAME ${PROJECT_NAME}_tests)
file(GLOB_RECURSE TEST_SOURCES *.cpp *.h *.hpp)

add_executable(${TESTS_NAME} EXCLUDE_FROM_ALL ${TEST_SOURCES})
target_compile_features(${TESTS_NAME} PUBLIC cxx_std_17)
target_link_libraries(${TESTS_NAME}
        ${PROJECT_NAME}
        Catch2::Catch2
        Boost::boost
        Boost::system)

# boost::asio
if(WIN32)
    target_link_libraries(${TESTS_NAME} ws2_32 wsock32)
else()
    find_library(PTHREAD_LIBRARY pthread)
    target_link_libraries(${TESTS_NAME} ${PTHREAD_LIBRARY})
endif()