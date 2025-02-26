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

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
    void Print(std::ostream& stream) const override;
    std::string GetIdentifier() const { return init_declarator_->GetIdentifier(); }

};

class VariableCall : public Node
{
private:
     std::string identifier_;
public:
    VariableCall(std::string identifier) : identifier_(identifier){};
    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
    void Print(std::ostream& stream) const override;
    std::string GetIdentifier() const { return identifier_; }
};
class VariableAssign : public Node
{
    private:
        std::string identifier_;
        NodePtr expression_;
        std::string op_;
    public:
        VariableAssign(std::string identifier, NodePtr expression, std::string op = "") : identifier_(identifier), expression_(std::move(expression)), op_(op) {};
        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
        void Print(std::ostream& stream) const override;
        std::string GetIdentifier() const { return identifier_; }
};

class VariablePostInc : public Node
{
    private:
        std::string identifier_;

    public:
        VariablePostInc(std::string identifier) : identifier_(identifier){};

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
        void Print(std::ostream& stream) const override;
        std::string GetIdentifier() const { return identifier_; }
};

class VariablePostDec : public Node
{
    private:
        std::string identifier_;

    public:
        VariablePostDec(std::string identifier) : identifier_(identifier){};

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
        void Print(std::ostream& stream) const override;
        std::string GetIdentifier() const { return identifier_; }

};

} // namespace ast
