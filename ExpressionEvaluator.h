#ifndef EXPRESSION_EVALUATOR_H_
#define EXPRESSION_EVALUATOR_H_

#include <string>
#include "AstExpressions.h"

class ExpressionEvaluator : public ast::IExpressionVisitor
{
public:
    ExpressionEvaluator();
    void Visit(ast::NumberExp& number);
    void Visit(ast::BooleanExp& boolean);
    void Visit(ast::BinaryExp& expression);
    void Visit(ast::UnaryExp& expression);
    int32_t Result() const;
    bool TruthResult() const;
private:
    enum ResultType
    {
        Unknown,
        Numeric,
        Boolean
    };
    ResultType resultType_ = ResultType::Unknown;
    int32_t result_ = 0;
    bool truthResult_ = false;
};

#endif // EXPRESSION_PRINTER_H_

