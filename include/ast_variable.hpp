#pragma once

#include "ast_node.hpp"
#include "ast_context.hpp"
#include <string>

namespace ast {

class Variable : public Node
{
private:
     const TypeSpecifier declaration_specifiers_;
     NodePtr init_declarator_;


public:
    Variable(const TypeSpecifier declaration_specifiers, NodePtr init_declarator) : declaration_specifiers_(declaration_specifiers), init_declarator_(std::move(init_declarator)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
