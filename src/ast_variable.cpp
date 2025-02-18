#include "ast_variable.hpp"
#include <string>
namespace ast {
    void VariableDeclare::EmitRISC(std::ostream& stream, Context& context) const
    {
        std::string identifier = init_declarator_->GetIdentifier();
        if (context.HasSymbol(identifier))
        {
            throw std::runtime_error("Variable already declared");
        }
        context.AddSymbol(identifier, declaration_specifiers_);
        init_declarator_->EmitRISC(stream, context);
        int offset = context.GetSymbol(identifier)->offset;
        stream << "sw a5, " << offset << "(sp)" << std::endl;
    }
    void VariableDeclare::Print(std::ostream& stream) const
    {
        stream << declaration_specifiers_ << " ";
        init_declarator_->Print(stream);
        stream << ";" << std::endl;
    }
    void VariableCall::EmitRISC(std::ostream& stream, Context& context) const
    {
        if (!context.HasSymbol(identifier_))
        {
            throw std::runtime_error("Variable not declared");
        }
        int offset = context.GetSymbol(identifier_)->offset;
        stream << "lw a5, " << offset << "(sp)" << std::endl;
    }
    void VariableCall::Print(std::ostream& stream) const
    {
        stream << identifier_;
    }
    void VariableAssign::EmitRISC(std::ostream& stream, Context& context) const
    {
        if (!context.HasSymbol(identifier_))
        {
            throw std::runtime_error("Variable not declared");
        }
        int offset = context.GetSymbol(identifier_)->offset;
        expression_->EmitRISC(stream, context);
        stream << "sw a5, " << offset << "(sp)" << std::endl;
    }
    void VariableAssign::Print(std::ostream& stream) const
    {
        stream << identifier_;
        stream << " = ";
        expression_->Print(stream);
        stream << ";" << std::endl;
    }
} // namespace ast
