
find_package(GTest CONFIG REQUIRED)

add_executable(zero2prod_tests health_check_test.cpp)
target_link_libraries(zero2prod_tests PRIVATE zero2prod_lib GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(zero2prod_tests)
