cmake_minimum_required(VERSION 3.10)

# set the project name
project(ast)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${GTEST_INCLUDE})

link_directories(${GTEST_LINK})

# add the executable
add_executable(ast_unittest AstExpressions.cpp AstUnitTest.cpp ExpressionPrinter.cpp ExpressionEvaluator.cpp)

target_link_libraries(ast_unittest gtest)
