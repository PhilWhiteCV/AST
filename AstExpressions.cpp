#include "AstExpressions.h"

using namespace ast;

NumberExp::NumberExp(int32_t value) : Value(value)
{
}
    
void NumberExp::Accept(IExpressionVisitor& visitor)
{
    visitor.Visit(*this);
}
        
void BinaryExp::Accept(IExpressionVisitor& visitor)
{
    visitor.Visit(*this);
}

BooleanExp::BooleanExp(bool value) : Value(value)
{
}

void BooleanExp::Accept(IExpressionVisitor& visitor)
{
    visitor.Visit(*this);
}

void UnaryExp::Accept(IExpressionVisitor& visitor)
{
    visitor.Visit(*this);
}
