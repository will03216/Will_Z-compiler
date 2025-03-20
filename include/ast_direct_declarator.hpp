#pragma once

#include "ast_node.hpp"

namespace ast {

class DirectDeclarator : public Node
{
private:
    NodePtr identifier_;
    NodePtr parameters_;
    int is_array_ ;

public:
DirectDeclarator(NodePtr identifier, NodePtr parameters = nullptr, int is_array = -1) : identifier_(std::move(identifier)), parameters_(std::move(parameters)), is_array_(is_array) {};

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    std::string GetIdentifier() const override { return identifier_->GetIdentifier(); };
    int IsArray() const override { return is_array_; };
    std::vector<TypeSpecifier> GetTypes(std::shared_ptr<Context> context) const override { return parameters_? parameters_->GetTypes(context) : std::vector<TypeSpecifier>{}; };
    int IsPointer(std::shared_ptr<Context>) const override { return 0; };

};

class Declarator : public Node
{
private:
    NodePtr direct_declarator_;
    int is_pointer_;

public:
    Declarator(NodePtr direct_declarator, int is_pointer = 0) : direct_declarator_(std::move(direct_declarator)), is_pointer_(is_pointer) {};

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    std::string GetIdentifier() const override { return direct_declarator_->GetIdentifier(); };
    int IsArray() const override { return direct_declarator_->IsArray(); };
    std::vector<TypeSpecifier> GetTypes(std::shared_ptr<Context> context) const override { return direct_declarator_->GetTypes(context); };
    int IsPointer(std::shared_ptr<Context>) const override { return is_pointer_; };
};

} // namespace ast
