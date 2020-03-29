#include "ExpressionEvaluator.h"
#include <iostream>

ExpressionEvaluator::ExpressionEvaluator()
{
}
    
void ExpressionEvaluator::Visit(ast::NumberExp& number)
{
    result_ = number.Value;
    resultType_ = ResultType::Numeric;
}

void ExpressionEvaluator::Visit(ast::BooleanExp& boolean)
{
    truthResult_ = boolean.Value;
    resultType_ = ResultType::Boolean;
}

void ExpressionEvaluator::Visit(ast::UnaryExp& expression)
{
    expression.value().Accept(*this);
    bool truth = truthResult_;
    
    switch (expression.type()) {
        case ast::ExpressionType::NOT:
            truthResult_ = !truthResult_;
            break;
        default:
            break;
    }
}

void ExpressionEvaluator::Visit(ast::BinaryExp& expression)
{
    expression.left().Accept(*this);
    int32_t leftValue = result_;
    bool leftTruth = truthResult_;
    ResultType leftResultType = resultType_;
    
    expression.right().Accept(*this);
    int32_t rightValue = result_;
    bool rightTruth = truthResult_;
    ResultType rightResultType = resultType_;
    
    switch (expression.type()) {
        case ast::ExpressionType::Addition:
            result_ = leftValue + rightValue;
            break;
        case ast::ExpressionType::Subtraction:
            result_ = leftValue - rightValue;
            break;
        case ast::ExpressionType::Multiplication:
            result_ = leftValue * rightValue;
            break;
        case ast::ExpressionType::Division:
            result_ = leftValue / rightValue;
            break;
        case ast::ExpressionType::AND:
            truthResult_ = leftTruth && rightTruth;
            break;
        case ast::ExpressionType::OR:
            truthResult_ = leftTruth || rightTruth;
            break;
        case ast::ExpressionType::Equality:
            /*
             * left and right results have to match
             * then
             * if the result type is numeric the values have to match
             *  OR
             * if the result type is boolean the truth values have to match
             */
            truthResult_ = ((leftResultType == rightResultType)
                            &&
                            ((resultType_ == ResultType::Numeric
                             &&
                             leftValue == rightValue)
                             ||
                             (resultType_ == ResultType::Boolean
                              &&
                              leftTruth == rightTruth)));
            break;

        default:
            break;
    }
}

int32_t ExpressionEvaluator::Result() const
{
    return result_;
}

bool ExpressionEvaluator::TruthResult() const
{
    return truthResult_;
}



