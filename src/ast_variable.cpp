#include "ast_variable.hpp"
#include <string>
namespace ast {
    void VariableDeclare::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string ) const
    {
        std::string identifier = init_declarator_->GetIdentifier();
        if (context->HasSymbol(identifier))
        {
            throw std::runtime_error("Variable already declared");
        }
        context->AddSymbol(identifier, declaration_specifiers_);
        init_declarator_->EmitRISC(stream, context, "a5");
        int offset = context->GetSymbol(identifier)->offset;
        stream << "sw a5, " << offset << "(s0)" << std::endl;
    }

    void VariableDeclare::Print(std::ostream& stream) const
    {
        stream << declaration_specifiers_ << " ";
        init_declarator_->Print(stream);
        stream << ";" << std::endl;
    }
    void VariableCall::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        int offset = context->GetScopedSymbol(identifier_)->offset;
        stream << "lw "<< destReg <<", " << offset << "(s0)" << std::endl;
    }



    void VariableCall::Print(std::ostream& stream) const
    {
        stream << identifier_;
    }
    void VariableAssign::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string ) const
    {
        int offset = context->GetScopedSymbol(identifier_)->offset;
        expression_->EmitRISC(stream, context, "a5");
        stream << "sw a5, " << offset << "(s0)" << std::endl;
    }
    void VariableAssign::Print(std::ostream& stream) const
    {
        stream << identifier_;
        stream << " = ";
        expression_->Print(stream);
        stream << ";" << std::endl;
    }
} // namespace ast
