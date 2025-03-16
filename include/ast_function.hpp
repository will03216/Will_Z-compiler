#pragma once

#include "ast_node.hpp"
#include "ast_type_specifier.hpp"

namespace ast {

class FunctionDefinition : public Node
{
private:
    const TypeSpecifier declaration_specifiers_;
    NodePtr declarator_;
    NodePtr compound_statement_;

public:
    FunctionDefinition(TypeSpecifier declaration_specifiers, NodePtr declarator, NodePtr compound_statement) : declaration_specifiers_(declaration_specifiers), declarator_(std::move(declarator)), compound_statement_(std::move(compound_statement)){};

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;

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

};


} // namespace ast
