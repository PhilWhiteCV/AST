
#include <limits.h>
#include "AstExpressions.h"
#include "ExpressionPrinter.h"
#include "ExpressionEvaluator.h"
#include "gtest/gtest.h"

TEST(ExpressionPrinter, Addition) {
  // emulate 1+2+3
  auto expression = std::make_unique<ast::BinaryExp>(
      std::make_unique<ast::BinaryExp>(
        std::make_unique<ast::NumberExp>(1),
        std::make_unique<ast::NumberExp>(2),
        ast::ExpressionType::Addition),
      std::make_unique<ast::NumberExp>(3),
      ast::ExpressionType::Addition);
  
  ExpressionPrinter expressionPrinter;
  expression->Accept(expressionPrinter);
    
  std::cout << expressionPrinter.Result() << std::endl;
  ASSERT_EQ(expressionPrinter.Result(), "1+2+3");
}

TEST(ExpressionPrinter, AdditionAndMultiplication) {
  // emulate 7*6+11
  auto expression = std::make_unique<ast::BinaryExp>(
        std::make_unique<ast::BinaryExp>(
          std::make_unique<ast::NumberExp>(7),
          std::make_unique<ast::NumberExp>(6),
          ast::ExpressionType::Multiplication),
        std::make_unique<ast::NumberExp>(11),
        ast::ExpressionType::Addition);

  ExpressionPrinter expressionPrinter;
  expression->Accept(expressionPrinter);
    
  std::cout << expressionPrinter.Result() << std::endl;
  ASSERT_EQ(expressionPrinter.Result(), "7*6+11");
}

TEST(ExpressionPrinter, SubtractionAndDivision) {
  // emulate 7/5-2
  auto expression = std::make_unique<ast::BinaryExp>(
        std::make_unique<ast::BinaryExp>(
          std::make_unique<ast::NumberExp>(7),
          std::make_unique<ast::NumberExp>(5),
          ast::ExpressionType::Division),
        std::make_unique<ast::NumberExp>(2),
        ast::ExpressionType::Subtraction);
  
  ExpressionPrinter expressionPrinter;
  expression->Accept(expressionPrinter);
    
  std::cout << expressionPrinter.Result() << std::endl;
  ASSERT_EQ(expressionPrinter.Result(), "7/5-2");
}

TEST(ExpressionPrinter, EvaluateLonger) {
  // emulate 10*4/2-5+10
  auto expression = std::make_unique<ast::BinaryExp>(
      std::make_unique<ast::NumberExp>(10),
      std::make_unique<ast::BinaryExp>(
             std::make_unique<ast::NumberExp>(4),
             std::make_unique<ast::BinaryExp>(
                    std::make_unique<ast::NumberExp>(2),
                    std::make_unique<ast::BinaryExp>(
                           std::make_unique<ast::NumberExp>(5),
                           std::make_unique<ast::NumberExp>(10),
                           ast::ExpressionType::Addition),
                    ast::ExpressionType::Subtraction),
             ast::ExpressionType::Division),
           ast::ExpressionType::Multiplication);

  ExpressionPrinter expressionPrinter;
  expression->Accept(expressionPrinter);
    
  std::cout << expressionPrinter.Result() << std::endl;
  ASSERT_EQ(expressionPrinter.Result(), "10*4/2-5+10");
}

TEST(ExpressionEvaluator, Addition) {
    // emulate 1+2+3
    auto expression = std::make_unique<ast::BinaryExp>(
          std::make_unique<ast::BinaryExp>(
            std::make_unique<ast::NumberExp>(1),
            std::make_unique<ast::NumberExp>(2),
            ast::ExpressionType::Addition),
          std::make_unique<ast::NumberExp>(3),
          ast::ExpressionType::Addition);
    
    ExpressionEvaluator expressionEvaluator;
    expression->Accept(expressionEvaluator);
      
    std::cout << "Result: " << expressionEvaluator.Result() << std::endl;
    ASSERT_EQ(expressionEvaluator.Result(), 6);
}

TEST(ExpressionEvaluator, AdditionAndMultiplication) {
  // emulate 7*6+11
  auto expression = std::make_unique<ast::BinaryExp>(
        std::make_unique<ast::BinaryExp>(
          std::make_unique<ast::NumberExp>(7),
          std::make_unique<ast::NumberExp>(6),
          ast::ExpressionType::Multiplication),
        std::make_unique<ast::NumberExp>(11),
        ast::ExpressionType::Addition);

  ExpressionEvaluator expressionEvaluator;
  expression->Accept(expressionEvaluator);
    
  std::cout << "Result: " << expressionEvaluator.Result() << std::endl;
  ASSERT_EQ(expressionEvaluator.Result(), 53);
}

TEST(ExpressionEvaluator, SubtractionAndDivision) {
  // emulate 10/5-2
  auto expression = std::make_unique<ast::BinaryExp>(
        std::make_unique<ast::BinaryExp>(
          std::make_unique<ast::NumberExp>(10),
          std::make_unique<ast::NumberExp>(5),
          ast::ExpressionType::Division),
        std::make_unique<ast::NumberExp>(2),
        ast::ExpressionType::Subtraction);
  
  ExpressionEvaluator expressionEvaluator;
  expression->Accept(expressionEvaluator);
    
  std::cout << "Result: " << expressionEvaluator.Result() << std::endl;
  ASSERT_EQ(expressionEvaluator.Result(), 0);
}

TEST(ExpressionEvaluator, BooleanAND) {
    // emulate true AND true
    auto expression = std::make_unique<ast::BinaryExp>(
                        std::make_unique<ast::BooleanExp>(true),
                        std::make_unique<ast::BooleanExp>(true),
                        ast::ExpressionType::AND);
    
    ExpressionEvaluator expressionEvaluator;
    expression->Accept(expressionEvaluator);
      
    std::cout << "Result: " << std::boolalpha << expressionEvaluator.TruthResult() << std::endl;
    ASSERT_EQ(expressionEvaluator.TruthResult(), true);
}

TEST(ExpressionEvaluator, BooleanANDandOR) {
    // emulate true AND false OR true
    auto expression = std::make_unique<ast::BinaryExp>(
                        std::make_unique<ast::BooleanExp>(true),
                          std::make_unique<ast::BinaryExp>(
                            std::make_unique<ast::BooleanExp>(false),
                            std::make_unique<ast::BooleanExp>(true),
                            ast::ExpressionType::OR),
                        ast::ExpressionType::AND);
    
    ExpressionEvaluator expressionEvaluator;
    expression->Accept(expressionEvaluator);
      
    std::cout << "Result: " << std::boolalpha << expressionEvaluator.TruthResult() << std::endl;
    ASSERT_EQ(expressionEvaluator.TruthResult(), true);
}

TEST(ExpressionEvaluator, BooleanNOT) {
    // emulate NOT true
    auto expression = std::make_unique<ast::UnaryExp>(
                        std::make_unique<ast::BooleanExp>(true),
                        ast::ExpressionType::NOT);
    
    ExpressionEvaluator expressionEvaluator;
    expression->Accept(expressionEvaluator);
      
    std::cout << "Result: " << std::boolalpha << expressionEvaluator.TruthResult() << std::endl;
    ASSERT_EQ(expressionEvaluator.TruthResult(), false);
}

TEST(ExpressionEvaluator, BooleanANDandNOT) {
    // emulate true AND NOT false
    auto expression = std::make_unique<ast::BinaryExp>(
                        std::make_unique<ast::BooleanExp>(true),
                          std::make_unique<ast::UnaryExp>(
                            std::make_unique<ast::BooleanExp>(false),
                            ast::ExpressionType::NOT),
                          ast::ExpressionType::AND);
    
    ExpressionEvaluator expressionEvaluator;
    expression->Accept(expressionEvaluator);
      
    std::cout << "Result: " << std::boolalpha << expressionEvaluator.TruthResult() << std::endl;
    ASSERT_EQ(expressionEvaluator.TruthResult(), true);
    
    ExpressionPrinter expressionPrinter;
    expression->Accept(expressionPrinter);
      
    std::cout << expressionPrinter.Result() << std::endl;
    ASSERT_EQ(expressionPrinter.Result(), "trueAND!false");
}

TEST(ExpressionEvaluator, EqualityBooleanTRUE) {
    auto expression = std::make_unique<ast::BinaryExp>(
                        std::make_unique<ast::BooleanExp>(true),
                        std::make_unique<ast::BooleanExp>(true),
                        ast::ExpressionType::Equality);
    
    ExpressionEvaluator expressionEvaluator;
    expression->Accept(expressionEvaluator);
      
    std::cout << "Result: " << std::boolalpha << expressionEvaluator.TruthResult() << std::endl;
    ASSERT_EQ(expressionEvaluator.TruthResult(), true);
}

TEST(ExpressionEvaluator, EqualityBooleanFAIL) {
    auto expression = std::make_unique<ast::BinaryExp>(
                        std::make_unique<ast::BooleanExp>(true),
                          std::make_unique<ast::BinaryExp>(
                            std::make_unique<ast::BooleanExp>(false),
                            std::make_unique<ast::BooleanExp>(false),
                            ast::ExpressionType::OR),
                        ast::ExpressionType::Equality);
    
    ExpressionEvaluator expressionEvaluator;
    expression->Accept(expressionEvaluator);
      
    std::cout << "Result: " << std::boolalpha << expressionEvaluator.TruthResult() << std::endl;
    ASSERT_EQ(expressionEvaluator.TruthResult(), false);
}

TEST(ExpressionEvaluator, EqualityNumericTRUE) {
    auto expression = std::make_unique<ast::BinaryExp>(
                        std::make_unique<ast::NumberExp>(10),
                        std::make_unique<ast::NumberExp>(10),
                        ast::ExpressionType::Equality);
    
    ExpressionEvaluator expressionEvaluator;
    expression->Accept(expressionEvaluator);
      
    std::cout << "Result: " << std::boolalpha << expressionEvaluator.TruthResult() << std::endl;
    ASSERT_EQ(expressionEvaluator.TruthResult(), true);
}

TEST(ExpressionEvaluator, EqualityNumericFAIL) {
    auto expression = std::make_unique<ast::BinaryExp>(
                        std::make_unique<ast::NumberExp>(10),
                          std::make_unique<ast::BinaryExp>(
                            std::make_unique<ast::NumberExp>(6),
                            std::make_unique<ast::NumberExp>(2),
                            ast::ExpressionType::Multiplication),
                        ast::ExpressionType::Equality);
    
    ExpressionEvaluator expressionEvaluator;
    expression->Accept(expressionEvaluator);
      
    std::cout << "Result: " << std::boolalpha << expressionEvaluator.TruthResult() << std::endl;
    ASSERT_EQ(expressionEvaluator.TruthResult(), false);
}

//cmake . -DGTEST_INCLUDE=../googletest-release-1.8.0/googletest/include/ -DGTEST_LINK=./

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv); 
  return RUN_ALL_TESTS();
}

