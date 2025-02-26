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
        if (op_ == "+=")
        {
            stream << "lw t0, " << offset << "(s0)" << std::endl;
            stream << "add a5, a5, t0" << std::endl;
        }
        else if (op_ == "-=")
        {
            stream << "lw t0, " << offset << "(s0)" << std::endl;
            stream << "sub a5, t0, a5" << std::endl;
        }
        else if (op_ == "*=")
        {
            stream << "lw t0, " << offset << "(s0)" << std::endl;
            stream << "mul a5, a5, t0" << std::endl;
        }
        else if (op_ == "/=")
        {
            stream << "lw t0, " << offset << "(s0)" << std::endl;
            stream << "div a5, a5, t0" << std::endl;
        }
        else if (op_ == "%=")
        {
            stream << "lw t0, " << offset << "(s0)" << std::endl;
            stream << "rem a5, a5, t0" << std::endl;
        }
        stream << "sw a5, " << offset << "(s0)" << std::endl;
    }
    void VariableAssign::Print(std::ostream& stream) const
    {
        stream << identifier_;
        stream << " = ";
        expression_->Print(stream);

        stream << ";" << std::endl;
    }


    void VariablePostInc::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        int offset = context->GetScopedSymbol(identifier_)->offset;
        stream << "lw " << destReg << ", " << offset << "(s0)" << std::endl;
        stream << "addi t0, " << destReg << ", 1" << std::endl;
        stream << "sw t0, " << offset << "(s0)" << std::endl;
    }

    void VariablePostInc::Print(std::ostream& stream) const
    {
        stream << identifier_;
        stream << "++";
    }

    void VariablePostDec::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        int offset = context->GetScopedSymbol(identifier_)->offset;
        stream << "lw " << destReg << ", " << offset << "(s0)" << std::endl;
        stream << "addi t0, " << destReg << ", -1" << std::endl;
        stream << "sw t0, " << offset << "(s0)" << std::endl;
    }

    void VariablePostDec::Print(std::ostream& stream) const
    {
        stream << identifier_;
        stream << "--";
    }


} // namespace ast
