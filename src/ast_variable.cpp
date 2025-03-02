#include "ast_variable.hpp"
#include <string>
namespace ast {
    void VariableDeclare::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string ) const
    {
        if (init_declarator_->IsArray() == -1)

        {
            std::string identifier = init_declarator_->GetIdentifier();
            if (context->HasSymbol(identifier))
            {
                throw std::runtime_error("Variable already declared");
            }
            int offset = context->AddSymbol(identifier, declaration_specifiers_);
            init_declarator_->EmitRISC(stream, context, "a5");
            stream << "sw a5, " << offset << "(s0)" << std::endl;
        }
        else {
            std::string identifier = init_declarator_->GetIdentifier();
            if (context->HasSymbol(identifier))
            {
                throw std::runtime_error("Variable already declared");
            }
            context->AddArray(identifier, declaration_specifiers_, init_declarator_->IsArray());
        }


    }

    void VariableDeclare::Print(std::ostream& stream) const
    {
        stream << declaration_specifiers_ << " ";
        init_declarator_->Print(stream);
        stream << ";" << std::endl;
        if (init_declarator_->IsArray() != -1)
        {
            stream << "int " << init_declarator_->GetIdentifier() << "[" << init_declarator_->IsArray() << "];" << std::endl;
        }
    }
    void VariableCall::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        if (index_ == nullptr)
        {
            int offset = context->GetScopedSymbol(identifier_)->offset;
            stream << "lw "<< destReg <<", " << offset << "(s0)" << std::endl;
        }
        else
        {
            // ensure a4 is not lost if it is an lhs (temp solution, think of a better way to do this)
            stream << "add sp, sp, -4" << std::endl;
            stream << "sw a4, 0(sp)" << std::endl;
            index_->EmitRISC(stream, context, "t1");
            stream << "li t0, -4" << std::endl;
            stream << "mul t1, t1, t0" << std::endl;
            //only implementing int array
            int offset = context->GetScopedSymbol(identifier_)->offset;
            stream << "li t0, " << offset << std::endl;
            stream << "add "<< destReg <<", t1, t0" << std::endl; // store the address of the array in a3 for use later (need to save this later)
            stream << "add " << destReg << ", "<< destReg <<", s0" << std::endl;
            stream << "lw "<< destReg <<", 0("<< destReg <<")" << std::endl;
            stream << "lw a4, 0(sp)" << std::endl;
            stream << "add sp, sp, 4" << std::endl;
        }

        //int offset = context->GetScopedSymbol(identifier_)->offset;
        //stream << "lw "<< destReg <<", " << offset << "(s0)" << std::endl;
    }



    void VariableCall::Print(std::ostream& stream) const
    {
        if(index_ == nullptr)
        {
            stream << identifier_;
        }
        else
        {
            stream << identifier_ << "[";
            index_->Print(stream);
            stream << "]";
        }
    }
    void VariableCall::EmitValueRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        if (index_ == nullptr)
        {
            int offset = context->GetScopedSymbol(identifier_)->offset;
            stream << "li "<< destReg <<", " << offset << std::endl;
            stream  << "add " << destReg << ", "<< destReg <<", s0" << std::endl;
        }
        else
        {
            stream << "add sp, sp, -4" << std::endl;
            stream << "sw a4, 0(sp)" << std::endl;
            index_->EmitRISC(stream, context, "t1");
            stream << "li t0, -4" << std::endl;
            stream << "mul t1, t1, t0" << std::endl;
            //only implementing int array
            int offset = context->GetScopedSymbol(identifier_)->offset;
            stream << "li t0, " << offset << std::endl;
            stream << "add "<< destReg <<", t1, t0" << std::endl; // store the address of the array in a3 for use later (need to save this later)
            stream << "add " << destReg << ", "<< destReg <<", s0" << std::endl;
            //is this necessary here?
            stream << "lw a4, 0(sp)" << std::endl;
            stream << "add sp, sp, 4" << std::endl;
        }
    }

    void VariableAssign::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        if (identifier_->IsArray() == -1)
        {
            // gets the offset of the variable and moves it into a3
            int offset = context->GetScopedSymbol(identifier_->GetIdentifier())->offset;
            stream << "li t2, " << offset << std::endl;
            stream  << "add t2, t2, s0" << std::endl;
        }
        else
        {
            // get the address of the array into a3
            identifier_->EmitValueRISC(stream, context, "t2");
        }

        expression_->EmitRISC(stream, context, destReg);
        if (op_ == "+=")
        {
            stream << "lw t0, 0(t2)" << std::endl;
            stream << "add " << destReg << ", "<< destReg <<", t0" << std::endl;
        }
        else if (op_ == "-=")
        {
            stream << "lw t0, 0(t2)" << std::endl;
            stream << "sub "<< destReg <<", t0, "<< destReg << std::endl;
        }
        else if (op_ == "*=")
        {
            stream << "lw t0, 0(t2)" << std::endl;
            stream << "mul " << destReg << ", "<< destReg <<", t0" << std::endl;
        }
        else if (op_ == "/=")
        {
            stream << "lw t0, 0(t2)" << std::endl;
            stream << "div " << destReg << ", "<< destReg <<", t0" << std::endl;
        }
        else if (op_ == "%=")
        {
            stream << "lw t0, 0(t2)" << std::endl;;
            stream << "rem " << destReg << ", "<< destReg <<", t0" << std::endl;
        }

        stream << "sw " << destReg <<", 0(t2)" << std::endl;
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
