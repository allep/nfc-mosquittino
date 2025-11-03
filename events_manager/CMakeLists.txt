cmake_minimum_required(VERSION 4.1)

project(EventsManager)
set(CMAKE_CXX_STANDARD 20)

enable_testing()

find_package(GTest REQUIRED)

file(GLOB SOURCES "app/*.cpp")
add_library(common_lib 
    app/EventsManager.cpp
    app/StaticContainer.h
)

add_executable(events_manager_tests tests/EventsManagerTests.cpp)
target_include_directories(events_manager_tests PRIVATE app)
target_link_libraries(events_manager_tests common_lib)
target_link_libraries(events_manager_tests GTest::gtest GTest::gtest_main)

add_executable(static_container_tests tests/StaticContainerTests.cpp)
target_include_directories(static_container_tests PRIVATE app)
target_link_libraries(static_container_tests common_lib)
target_link_libraries(static_container_tests GTest::gtest GTest::gtest_main)

add_test(NAME events_manager_tests COMMAND events_manager_tests)
add_test(NAME static_container_tests COMMAND static_container_tests)
