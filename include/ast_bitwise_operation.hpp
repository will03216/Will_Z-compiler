#pragma once

#include "ast_node.hpp"

namespace ast {

class BitwiseAndExpr : public Node
{
private:
    NodePtr lhs_;
    NodePtr rhs_;

public:
    BitwiseAndExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier GetType() const override { return lhs_->GetType(); }
};

class BitwiseInlcusiveOrExpr : public Node
{
private:
    NodePtr lhs_;
    NodePtr rhs_;

public:
    BitwiseInlcusiveOrExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier GetType() const override { return lhs_->GetType(); }
};

class BitwiseExclusiveOrExpr : public Node
{
private:
    NodePtr lhs_;
    NodePtr rhs_;

public:
    BitwiseExclusiveOrExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier GetType() const override { return lhs_->GetType(); }
};

}  // namespace ast
