cmake_minimum_required(VERSION 4.1)

enable_testing()

find_package(GTest REQUIRED)
add_executable(foo_test tests/foo_test.cpp)
target_link_libraries(foo_test GTest::gtest GTest::gtest_main)

add_test(NAME foo_test COMMAND foo_test)
