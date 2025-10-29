cmake_minimum_required(VERSION 4.1)

project(EventsManager)
set(CMAKE_CXX_STANDARD 20)

enable_testing()

find_package(GTest REQUIRED)

set(SOURCES
    app/EventsManager.cpp
    tests/EventsManagerTests.cpp
)

add_executable(events_manager_tests ${SOURCES})

target_include_directories(events_manager_tests PRIVATE app)
target_link_libraries(events_manager_tests GTest::gtest GTest::gtest_main)

add_test(NAME events_manager_tests COMMAND events_manager_tests)
