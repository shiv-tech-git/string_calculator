cmake_minimum_required(VERSION 2.6)
project(runTests)


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(runTests calc_tests.cpp ../src/ExpressionParser.cpp ../src/ExpressionTree.cpp ../src/StringCalculator.cpp ../src/TreeCalculator.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

target_include_directories(runTests PUBLIC ../include )