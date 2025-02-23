
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
    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
