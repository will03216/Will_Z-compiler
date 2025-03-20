#pragma once

#include "ast_node.hpp"

namespace ast {

class AddressOfExpr : public Node
{
private:
    NodePtr expr_;

public:
    AddressOfExpr(NodePtr expr) : expr_(std::move(expr)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier GetType(std::shared_ptr<Context>) const override { return TypeSpecifier::INT; }
    std::string GetIdentifier() const { return expr_->GetIdentifier(); }
};

class DereferenceExpr : public Node
{
private:
    NodePtr expr_;

public:
    DereferenceExpr(NodePtr expr) : expr_(std::move(expr)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    std::string GetIdentifier() const { return expr_->GetIdentifier(); }
    TypeSpecifier GetType(std::shared_ptr<Context>) const override { return TypeSpecifier::INT; }
    int IsPointer(std::shared_ptr<Context>) const override { return -1; }
    void EmitValueRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
};


} // namespace ast
