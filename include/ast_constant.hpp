#pragma once

#include "ast_node.hpp"

namespace ast {

class IntConstant : public Node
{
private:
    int value_;

public:
    IntConstant(int value) : value_(value) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
