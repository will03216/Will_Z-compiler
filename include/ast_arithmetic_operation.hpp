#pragma once

#include "ast_node.hpp"

namespace ast {

class AddExpr : public Node
{
private:
    int lhs_;
    int rhs_;

public:
    AddExpr(int lhs, int rhs) : lhs_(lhs), rhs_(rhs) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
