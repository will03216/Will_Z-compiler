#pragma once

#include "ast_node.hpp"
#include <string>

namespace ast {

class InitDeclarator : public Node
{
private:
     NodePtr declarator_;
     NodePtr initializer_;

public:
    InitDeclarator(NodePtr declarator, NodePtr initializer) : declarator_(std::move(declarator)), initializer_(std::move(initializer)){};

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    std::string GetIdentifier() const override { return declarator_->GetIdentifier(); };
    int IsArray() const override { return declarator_->IsArray(); };
    int IsPointer(std::shared_ptr<Context> context) const override { return declarator_->IsPointer(context); };
    std::vector<std::variant<int, float, double>> GetConstList() const override { return initializer_?initializer_->GetConstList():std::vector<std::variant<int, float, double>>(); };
};

class Initializer : public Node
{
private:
    NodePtr expression_;

public:
    Initializer(NodePtr expression) : expression_(std::move(expression)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    std::variant<int, float, double> GetConst() const override { return expression_->GetConst(); };
    std::vector<std::variant<int, float, double>> GetConstList() const override { return expression_->GetConstList(); };
    TypeSpecifier GetType(std::shared_ptr<Context> context) const override { return expression_->GetType(context); };
    int IsPointer(std::shared_ptr<Context> context) const override { return expression_->IsPointer(context); };
    int IsArray() const override { return expression_->IsArray(); };
};

} // namespace ast
