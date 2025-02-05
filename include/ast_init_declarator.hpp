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

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
