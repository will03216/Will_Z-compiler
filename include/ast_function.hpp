#pragma once

#include "ast_node.hpp"
#include "ast_type_specifier.hpp"

namespace ast {

class FunctionDefinition : public Node
{
private:
    NodePtr declaration_specifiers_;
    NodePtr declarator_;
    NodePtr compound_statement_;

public:
    FunctionDefinition(NodePtr declaration_specifiers, NodePtr declarator, NodePtr compound_statement) : declaration_specifiers_(std::move(declaration_specifiers)), declarator_(std::move(declarator)), compound_statement_(std::move(compound_statement)){};

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier GetType(std::shared_ptr<Context> context) const override { return declaration_specifiers_->GetType(context); }
    int IsPointer(std::shared_ptr<Context> context) const override { return declarator_->IsPointer(context); }
};

class FunctionCall : public Node
{
private:
    NodePtr identifier_;
    NodePtr argument_expression_list_;

public:
    FunctionCall(NodePtr identifier, NodePtr argument_expression_list) : identifier_(std::move(identifier)), argument_expression_list_(std::move(argument_expression_list)){};

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier GetType(std::shared_ptr<Context> context) const override { return context->GetFunction(identifier_->GetIdentifier())->return_type; }
    //int IsPointer(std::shared_ptr<Context> context) const override { return context->GetFunction(identifier_->GetIdentifier())->is_pointer; }
};


} // namespace ast
