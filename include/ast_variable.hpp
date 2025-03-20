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

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    std::string GetIdentifier() const { return init_declarator_->GetIdentifier(); }
    int IsArray() const { return init_declarator_->IsArray(); }
    TypeSpecifier GetType(std::shared_ptr<Context> ) const { return declaration_specifiers_; }
    int IsPointer(std::shared_ptr<Context> context) const { return init_declarator_->IsPointer(context); }
};

class VariableCall : public Node
{
private:
     std::string identifier_;
     NodePtr index_;


public:
    VariableCall(std::string identifier, NodePtr index) : identifier_(identifier), index_(std::move(index)) {};



    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    std::string GetIdentifier() const { return identifier_; }
    int IsArray() const { return index_ ? 0 : -1; }
    void EmitValueRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
    TypeSpecifier GetType(std::shared_ptr<Context> context) const { return context->GetScopedSymbol(identifier_)->type; }
    int IsPointer(std::shared_ptr<Context> context) const {
        return context->GetScopedSymbol(identifier_)->isPointer; }
    };

class VariableAssign : public Node
{
    private:
        NodePtr identifier_;
        NodePtr expression_;
        std::string op_;

    public:
        VariableAssign(NodePtr identifier, NodePtr expression, std::string op = "") : identifier_(std::move(identifier)), expression_(std::move(expression)), op_(op) {};

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
        std::string GetIdentifier() const { return identifier_->GetIdentifier(); }
        TypeSpecifier GetType(std::shared_ptr<Context> context) const { return identifier_->GetType(context); }
        int IsPointer(std::shared_ptr<Context> context) const { return identifier_->IsPointer(context); }
};

class VariablePostInc : public Node
{
    private:
        std::string identifier_;

    public:
        VariablePostInc(std::string identifier) : identifier_(identifier){};

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
        std::string GetIdentifier(std::shared_ptr<Context>) const { return identifier_; }
        // Implement GetType
        // Implement IsPointer
};

class VariablePostDec : public Node
{
    private:
        std::string identifier_;

    public:
        VariablePostDec(std::string identifier) : identifier_(identifier){};

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
        std::string GetIdentifier() const { return identifier_; }
        // Implement GetType
        // Implement IsPointer
};

} // namespace ast
