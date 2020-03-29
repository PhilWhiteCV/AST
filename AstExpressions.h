#ifndef AST_EXPRESSIONS_H_
#define AST_EXPRESSIONS_H_

#include <memory>

namespace ast
{
    class NumberExp;
    class BinaryExp;
    class BooleanExp;
    class UnaryExp;

    enum ExpressionType
    {
        Addition,
        Subtraction,
        Multiplication,
        Division,
        AND,
        OR,
        NOT,
        Equality
    };

    class IExpressionVisitor
    {
    public:
        virtual void Visit(NumberExp& number) = 0;
        virtual void Visit(BooleanExp& boolean) = 0;
        virtual void Visit(BinaryExp& expression) = 0;
        virtual void Visit(UnaryExp& expression) = 0;
    };

    class IExpression
    {
    public:
       virtual ~IExpression() = 0;
       virtual void Accept(IExpressionVisitor& visitor) = 0;
    };

    inline IExpression::~IExpression() = default;
    using IExpressionPtr = std::unique_ptr<IExpression>;

    class BinaryExp : public IExpression {
      IExpressionPtr Left;
      IExpressionPtr Right;
      ExpressionType Type;
    public:
      BinaryExp(IExpressionPtr left, IExpressionPtr right, ExpressionType type)
        : Left(move(left)), Right(move(right)), Type(type)
      { assert(Left && Right); }
  
      void Accept(IExpressionVisitor& visitor);
      IExpression& left() { return *Left; }
      IExpression& right() { return *Right; }
      ExpressionType type() { return Type; }
    };

    class UnaryExp : public IExpression {
        IExpressionPtr Value;
        ExpressionType Type;
      public:
        UnaryExp(IExpressionPtr value, ExpressionType type)
          : Value(move(value)), Type(type)
        { assert(Value); }

        void Accept(IExpressionVisitor& visitor);
        IExpression& value() { return *Value; }
        ExpressionType type() { return Type; }
      };

    class NumberExp : public IExpression
    {
    public:
        NumberExp(int32_t value);
        void Accept(IExpressionVisitor& visitor);
        const int32_t Value;
    };

    class BooleanExp : public IExpression
    {
    public:
        BooleanExp(bool value);
        void Accept(IExpressionVisitor& visitor);
        const bool Value;
    };
}

#endif // AST_EXPRESSIONS_H_
