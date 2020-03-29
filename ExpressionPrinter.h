#ifndef EXPRESSION_PRINTER_H_
#define EXPRESSION_PRINTER_H_

#include <string>
#include "AstExpressions.h"

class ExpressionPrinter : public ast::IExpressionVisitor
{
public:
    ExpressionPrinter();
    void Visit(ast::NumberExp& number);
    void Visit(ast::BooleanExp& boolean);
    void Visit(ast::BinaryExp& expression);
    void Visit(ast::UnaryExp& expression);
    const std::string& Result() const;
private:
    void ComposeBinaryOp(ast::BinaryExp& exp, const std::string& op);
    std::string result_;
};

#endif // EXPRESSION_PRINTER_H_

