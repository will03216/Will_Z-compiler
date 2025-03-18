#pragma once

#include "ast_node.hpp"

namespace ast
{

    class LessThanExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        LessThanExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type ) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return TypeSpecifier::INT; }
    };

    class GreaterThanExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        GreaterThanExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type ) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return TypeSpecifier::INT; }
    };

    class LessThanEqualExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        LessThanEqualExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type ) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return TypeSpecifier::INT; }
    };

    class GreaterThanEqualExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        GreaterThanEqualExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type ) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return TypeSpecifier::INT; }
    };

    class EqualityExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        EqualityExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type ) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return TypeSpecifier::INT; }
    };
    class InequalityExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        InequalityExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type ) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return TypeSpecifier::INT; }
    };

    class LogicalAndExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        LogicalAndExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type ) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return TypeSpecifier::INT; }
    };

    class LogicalOrExpr : public Node
    {
    private:
        NodePtr lhs_;
        NodePtr rhs_;

    public:
        LogicalOrExpr(NodePtr lhs, NodePtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type ) const override;
        void Print(std::ostream &stream) const override;
        TypeSpecifier GetType() const override { return TypeSpecifier::INT; }
    };

} // namespace ast
