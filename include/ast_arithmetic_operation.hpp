#pragma once

#include "ast_node.hpp"

namespace ast {

class AddExpr : public Node
{
private:
    NodePtr lhs_;
    NodePtr rhs_;

public:
    AddExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const override;
    void Print(std::ostream& stream) const override;
};

class SubExpr : public Node
{
private:
    NodePtr lhs_;
    NodePtr rhs_;

public:
    SubExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
