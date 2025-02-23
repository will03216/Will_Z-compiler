#pragma once

#include "ast_node.hpp"

namespace ast {

class LessThanExpr : public Node
{
private:
    NodePtr lhs_;
    NodePtr rhs_;

public:
LessThanExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const override;
    void Print(std::ostream& stream) const override;
};

class GreaterThanExpr : public Node
{
private:
    NodePtr lhs_;
    NodePtr rhs_;
public:
GreaterThanExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const override;
    void Print(std::ostream& stream) const override;
};

class LessThanEqualExpr : public Node
{
private:
    NodePtr lhs_;
    NodePtr rhs_;
public:
LessThanEqualExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const override;
    void Print(std::ostream& stream) const override;
};

class GreaterThanEqualExpr : public Node
{
private:
    NodePtr lhs_;
    NodePtr rhs_;
public:
GreaterThanEqualExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const override;
    void Print(std::ostream& stream) const override;
};

class EqualityExpr : public Node
{
private:
    NodePtr lhs_;
    NodePtr rhs_;
public:
EqualityExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const override;
    void Print(std::ostream& stream) const override;
};
class InequalityExpr : public Node
{
private:
    NodePtr lhs_;
    NodePtr rhs_;
public:
InequalityExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const override;
    void Print(std::ostream& stream) const override;
};


} // namespace ast
