#pragma once
#include "ast_node.hpp"
namespace ast {
class CompoundStatement : public Node
{
private:
    NodePtr expression_;
public:
    CompoundStatement(NodePtr expression) : expression_(std::move(expression)) {}
    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
};
} // namespace ast
