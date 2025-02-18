#pragma once

#include "ast_node.hpp"
#include "ast_context.hpp"
#include <string>

namespace ast {

class VariableDeclare : public Node
{
private:
     const TypeSpecifier declaration_specifiers_;
     NodePtr init_declarator_;


public:
    VariableDeclare(const TypeSpecifier declaration_specifiers, NodePtr init_declarator) : declaration_specifiers_(declaration_specifiers), init_declarator_(std::move(init_declarator)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class VariableCall : public Node
{
private:
     std::string identifier_;
public:
    VariableCall(std::string identifier) : identifier_(identifier){};
    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};
class VariableAssign : public Node
{
    private:
        std::string identifier_;
        NodePtr expression_;
    public:
        VariableAssign(std::string identifier, NodePtr expression) : identifier_(identifier), expression_(std::move(expression)){};
        void EmitRISC(std::ostream& stream, Context& context) const override;
        void Print(std::ostream& stream) const override;
};

} // namespace ast
