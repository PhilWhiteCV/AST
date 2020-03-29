#include "ExpressionPrinter.h"

ExpressionPrinter::ExpressionPrinter()
{
}
    
void ExpressionPrinter::Visit(ast::NumberExp& integer)
{
    result_ += std::to_string(integer.Value);
}

void ExpressionPrinter::Visit(ast::BooleanExp& boolean)
{
    result_ += (boolean.Value)?"true":"false";
}

void ExpressionPrinter::Visit(ast::UnaryExp& expression)
{
    switch (expression.type()) {
        case ast::ExpressionType::NOT:
            result_ += "!";
            expression.value().Accept(*this);
            break;
        default:
            break;
    }
}

void ExpressionPrinter::Visit(ast::BinaryExp& expression)
{
    switch (expression.type()) {
        case ast::ExpressionType::Addition:
            ComposeBinaryOp(expression, "+");
            break;
        case ast::ExpressionType::Subtraction:
            ComposeBinaryOp(expression, "-");
            break;
        case ast::ExpressionType::Multiplication:
            ComposeBinaryOp(expression, "*");
            break;
        case ast::ExpressionType::Division:
            ComposeBinaryOp(expression, "/");
            break;
        case ast::ExpressionType::AND:
            ComposeBinaryOp(expression, "AND");
            break;
        case ast::ExpressionType::OR:
            ComposeBinaryOp(expression, "OR");
            break;
        default:
            break;
    }
}

void ExpressionPrinter::ComposeBinaryOp(ast::BinaryExp& exp, const std::string& op)
{
    exp.left().Accept(*this);
    result_ += op;
    exp.right().Accept(*this);
}

const std::string& ExpressionPrinter::Result() const
{
    return result_;
}
