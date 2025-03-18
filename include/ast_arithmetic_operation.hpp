#pragma once

#include "ast_node.hpp"

namespace ast
{

    class AddExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        AddExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return lhs_->GetType(); }
    };

    class SubExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        SubExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return lhs_->GetType(); }
    };

    class MulExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        MulExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return lhs_->GetType(); }
    };

    class DivExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        DivExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return lhs_->GetType(); }
    };

    class ModExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        ModExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return lhs_->GetType(); }
    };

    class LeftShiftExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        LeftShiftExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return lhs_->GetType(); }
    };

    class RightShiftExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        RightShiftExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return lhs_->GetType(); }

    };

    class Negation : public Node
{
private:
    NodePtr expression_;

public:
    Negation(NodePtr expression) : expression_(std::move(expression)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier GetType() const override { return expression_->GetType(); }
};




}// namespace ast
