
#pragma once

#include "ast_node.hpp"

namespace ast {



class ArgumentExpressionList : public NodeList
{
private:
    std::vector<NodePtr> arguments_;
public:
    ArgumentExpressionList(NodePtr first_argument) {
        arguments_.push_back(std::move(first_argument));
    }

    void PushBack(NodePtr argument);
    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
};

class Parameter : public Node
{
private:
    TypeSpecifier type_;
    NodePtr identifier_;
public:
    Parameter(TypeSpecifier type, NodePtr identifier) : type_(type), identifier_(std::move(identifier)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    std::string GetIdentifier() const override;
    TypeSpecifier GetType(std::shared_ptr<Context> context) const override;
    int IsPointer(std::shared_ptr<Context> context) const override { return identifier_->IsPointer(context); }
};

} // namespace ast
