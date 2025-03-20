#include "ast_variable.hpp"
#include <string>

namespace ast {

    void VariableDeclare::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string, TypeSpecifier ) const
    {
        if (init_declarator_->IsArray() == -1)
        {
            std::string identifier = init_declarator_->GetIdentifier();
            if (context->HasSymbol(identifier))
            {
                throw std::runtime_error("Variable already declared");
            }
            int offset = context->AddSymbol(identifier, declaration_specifiers_, init_declarator_->IsPointer(context));

            if (declaration_specifiers_ == TypeSpecifier::INT)
            {
                init_declarator_->EmitRISC(stream, context, "a5", TypeSpecifier::INT);
                stream << "sw a5, " << offset << "(s0)" << std::endl;
            }
            else if (declaration_specifiers_ == TypeSpecifier::FLOAT)
            {
                init_declarator_->EmitRISC(stream, context, "a5", TypeSpecifier::FLOAT);
                stream << "fsw fa5, " << offset << "(s0)" << std::endl;
            }
            else if (declaration_specifiers_ == TypeSpecifier::DOUBLE)
            {
                init_declarator_->EmitRISC(stream, context, "a5", TypeSpecifier::DOUBLE);
                stream << "fsd fa5, " << offset << "(s0)" << std::endl;
            }
            else if (declaration_specifiers_ == TypeSpecifier::CHAR)
            {
                init_declarator_->EmitRISC(stream, context, "a5", TypeSpecifier::CHAR);
                stream << "sb a5, " << offset << "(s0)" << std::endl;
            }

            else
            {
                throw std::runtime_error("VariableDeclare: TypeSpecifier not supported");
            }
        }
        else {
            std::string identifier = init_declarator_->GetIdentifier();
            if (context->HasSymbol(identifier))
            {
                throw std::runtime_error("Variable already declared");
            }
            int offset = context->AddArray(identifier, declaration_specifiers_, init_declarator_->IsArray());

            std::vector<std::variant<int, float, double>> constList = init_declarator_->GetConstList();
            int size = static_cast<int>(constList.size());
            if (size > init_declarator_->IsArray())
            {
                std::cout << size << " " << init_declarator_->IsArray() << std::endl;
                throw std::runtime_error("VariableDeclare: Array size is too small");
            }

            for (int i = 0; i < size; i++)
            {
                if (declaration_specifiers_ == TypeSpecifier::INT)
                {
                    stream << "li a5, " << std::get<int>(constList[i]) << std::endl;
                    stream << "sw a5, " << offset + i * 4 << "(s0)" << std::endl;
                }
                else if (declaration_specifiers_ == TypeSpecifier::FLOAT)
                {
                    stream << "li a5, " << std::get<float>(constList[i]) << std::endl;
                    stream << "fsw fa5, " << offset + i * 4 << "(s0)" << std::endl;
                }
                else if (declaration_specifiers_ == TypeSpecifier::DOUBLE)
                {
                    stream << "li a5, " << std::get<double>(constList[i]) << std::endl;
                    stream << "fsd fa5, " << offset + i * 8 << "(s0)" << std::endl;
                }
                else if (declaration_specifiers_ == TypeSpecifier::CHAR)
                {
                    stream << "li a5, " << std::get<int>(constList[i]) << std::endl;
                    stream << "sb a5, " << offset + i << "(s0)" << std::endl;
                }
                else
                {
                    throw std::runtime_error("VariableDeclare: TypeSpecifier not supported");
                }
            }

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

    void VariableCall::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier) const
    {
        if (index_ == nullptr)
        {
            Symbol symbol = *context->GetScopedSymbol(identifier_);

            if (symbol.isPointer == 1){
                stream << "lw "<< destReg <<", " << symbol.offset << "(s0)" << std::endl;
                return;
            }

            if (symbol.type == TypeSpecifier::INT)
            {
                stream << "lw "<< destReg <<", " << symbol.offset << "(s0)" << std::endl;
            }
            else if (symbol.type == TypeSpecifier::FLOAT)
            {
                stream << "flw f"<< destReg <<", " << symbol.offset << "(s0)" << std::endl;
            }
            else if (symbol.type == TypeSpecifier::DOUBLE)
            {
                stream << "fld f"<< destReg <<", " << symbol.offset << "(s0)" << std::endl;
            }
            else if (symbol.type == TypeSpecifier::CHAR)
            {
                stream << "lb "<< destReg <<", " << symbol.offset << "(s0)" << std::endl;
            }
            else
            {
                throw std::runtime_error("VariableCall: TypeSpecifier not supported");
            }
        }
        else
        {
            Symbol symbol = *context->GetScopedSymbol(identifier_);
            index_->EmitRISC(stream, context, "a1", TypeSpecifier::INT);
            if (symbol.type == TypeSpecifier::INT)
            {
                stream << "slli a1, a1, 2" << std::endl;
            }
            else if (symbol.type == TypeSpecifier::FLOAT)
            {
                stream << "slli a1, a1, 2" << std::endl;
            }
            else if (symbol.type == TypeSpecifier::DOUBLE)
            {
                stream << "slli a1, a1, 3" << std::endl;
            }
            else if (symbol.type == TypeSpecifier::CHAR)
            {
                stream << "slli a1, a1, 0" << std::endl;
            }
            else
            {
                throw std::runtime_error("VariableCall: TypeSpecifier not supported");
            }

            if (symbol.isPointer == 1){
                stream << "li t0, " << symbol.offset << std::endl;
                stream << "add t0, t0, s0" << std::endl;
                stream << "lw t0, 0(t0)" << std::endl;
                stream << "add "<< destReg <<", a1, t0" << std::endl;
            } else {
                stream << "li t0, " << symbol.offset << std::endl;
                stream << "add "<< destReg <<", a1, t0" << std::endl;
                stream << "add " << destReg << ", "<< destReg <<", s0" << std::endl;
            }

            if (symbol.type == TypeSpecifier::INT)
            {
                stream << "lw "<< destReg <<", 0("<< destReg <<")" << std::endl;
            }
            else if (symbol.type == TypeSpecifier::FLOAT)
            {
                stream << "flw f"<< destReg <<", 0("<< destReg <<")" << std::endl;
            }
            else if (symbol.type == TypeSpecifier::DOUBLE)
            {
                stream << "fld f"<< destReg <<", 0("<< destReg <<")" << std::endl;
            }
            else if (symbol.type == TypeSpecifier::CHAR)
            {
                stream << "lb "<< destReg <<", 0("<< destReg <<")" << std::endl;
            }
            else
            {
                throw std::runtime_error("VariableCall: TypeSpecifier not supported");
            }
        }
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


    // There may be issues if the index is an array call
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
            Symbol symbol = *context->GetScopedSymbol(identifier_);
            index_->EmitRISC(stream, context, "a1", TypeSpecifier::INT);
            if (symbol.type == TypeSpecifier::INT)
            {
                stream << "slli a1, a1, 2" << std::endl;
            }
            else if (symbol.type == TypeSpecifier::FLOAT)
            {
                stream << "slli a1, a1, 2" << std::endl;
            }
            else if (symbol.type == TypeSpecifier::DOUBLE)
            {
                stream << "slli a1, a1, 3" << std::endl;
            }
            else
            {
                throw std::runtime_error("VariableCall: TypeSpecifier not supported");
            }
            if (symbol.isPointer == 1){
                stream << "li t0, " << symbol.offset << std::endl;
                stream << "add t0, t0, s0" << std::endl;
                stream << "lw t0, 0(t0)" << std::endl;
                stream << "add "<< destReg <<", a1, t0" << std::endl;
                return;
            }

            stream << "li t0, " << symbol.offset << std::endl;
            stream << "add "<< destReg <<", a1, t0" << std::endl;
            stream << "add " << destReg << ", "<< destReg <<", s0" << std::endl;
        }
    }

    void VariableAssign::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
    {

        Symbol symbol = *context->GetScopedSymbol(identifier_->GetIdentifier());
        if (identifier_->IsArray() == -1 && identifier_->IsPointer(context) != -1)
        {
            // gets the offset of the variable and moves it into a2
            stream << "li a2, " << symbol.offset << std::endl;
            stream  << "add a2, a2, s0" << std::endl;
        }
        else
        {
            // get the address of the array into a2
            identifier_->EmitValueRISC(stream, context, "a2");
        }

        if (symbol.type == TypeSpecifier::INT)
        {

            if (op_ != "="){
                stream << "lw t0, 0(a2)" << std::endl;
            }

            expression_->EmitRISC(stream, context, destReg, symbol.type);
            if (op_ == "+=")
            {
                stream << "add " << destReg << ", "<< destReg <<", t0" << std::endl;
            }
            else if (op_ == "-=")
            {
                stream << "sub "<< destReg <<", t0, "<< destReg << std::endl;
            }
            else if (op_ == "*=")
            {
                stream << "mul " << destReg << ", "<< destReg <<", t0" << std::endl;
            }
            else if (op_ == "/=")
            {
                stream << "div " << destReg << ", "<< destReg <<", t0" << std::endl;
            }
            else if (op_ == "%=")
            {
                stream << "rem " << destReg << ", "<< destReg <<", t0" << std::endl;
            }

            stream << "sw " << destReg <<", 0(a2)" << std::endl;
        }
        else if (symbol.type == TypeSpecifier::FLOAT)
        {
            if (op_ != "="){
                stream << "flw ft0, 0(a2)" << std::endl;
            }

            expression_->EmitRISC(stream, context, destReg, symbol.type);
            if (op_ == "+=")
            {
                stream << "fadd.s f" << destReg << ", f"<< destReg <<", ft0" << std::endl;
            }
            else if (op_ == "-=")
            {
                stream << "fsub.s f"<< destReg <<", ft0, f"<< destReg << std::endl;
            }
            else if (op_ == "*=")
            {
                stream << "fmul.s f" << destReg << ", f"<< destReg <<", ft0" << std::endl;
            }
            else if (op_ == "/=")
            {
                stream << "fdiv.s f" << destReg << ", f"<< destReg <<", ft0" << std::endl;
            }
            else if (op_ == "%=")
            {
                throw std::runtime_error("VariableAssign: TypeSpecifier not supported");
            }

            stream << "fsw f" << destReg <<", 0(a2)" << std::endl;
        }
        else if (symbol.type == TypeSpecifier::DOUBLE)
        {
            if (op_ != "="){
                stream << "fld ft0, 0(a2)" << std::endl;
            }

            expression_->EmitRISC(stream, context, destReg, symbol.type);
            if (op_ == "+=")
            {
                stream << "fadd.d f" << destReg << ", "<< destReg <<", ft0" << std::endl;
            }
            else if (op_ == "-=")
            {
                stream << "fsub.d f"<< destReg <<", ft0, "<< destReg << std::endl;
            }
            else if (op_ == "*=")
            {
                stream << "fmul.d f" << destReg << ", "<< destReg <<", ft0" << std::endl;
            }
            else if (op_ == "/=")
            {
                stream << "fdiv.d f" << destReg << ", "<< destReg <<", ft0" << std::endl;
            }
            else if (op_ == "%=")
            {
                throw std::runtime_error("VariableAssign: TypeSpecifier not supported");
            }

            stream << "fsd f" << destReg <<", 0(a2)" << std::endl;
        }
        else
        {
            throw std::runtime_error("VariableAssign: TypeSpecifier not supported");
        }

    }

    void VariableAssign::Print(std::ostream& stream) const
    {
        stream << identifier_;
        stream << " = ";
        expression_->Print(stream);
        stream << ";" << std::endl;
    }

    //change later
    void VariablePostInc::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
    {
        Symbol symbol = *context->GetScopedSymbol(identifier_);
        if (symbol.type == TypeSpecifier::INT)
        {
            stream << "lw " << destReg << ", " << symbol.offset << "(s0)" << std::endl;
            stream << "addi t0, " << destReg << ", 1" << std::endl;
            stream << "sw t0, " << symbol.offset << "(s0)" << std::endl;
        }
        else if (symbol.type == TypeSpecifier::FLOAT)
        {
            stream << "flw " << destReg << ", " << symbol.offset << "(s0)" << std::endl;
            stream << "fadd.s ft0, " << destReg << ", 1" << std::endl;
            stream << "fsw ft0, " << symbol.offset << "(s0)" << std::endl;
        }
        else if (symbol.type == TypeSpecifier::DOUBLE)
        {
            stream << "fld " << destReg << ", " << symbol.offset << "(s0)" << std::endl;
            stream << "fadd.d ft0, " << destReg << ", 1" << std::endl;
            stream << "fsd ft0, " << symbol.offset << "(s0)" << std::endl;
        }
        else
        {
            throw std::runtime_error("VariablePostInc: TypeSpecifier not supported");
        }
    }

    void VariablePostInc::Print(std::ostream& stream) const
    {
        stream << identifier_;
        stream << "++";
    }

    void VariablePostDec::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier) const
    {
        Symbol symbol = *context->GetScopedSymbol(identifier_);
        if (symbol.type == TypeSpecifier::INT)
        {
            stream << "lw " << destReg << ", " << symbol.offset << "(s0)" << std::endl;
            stream << "addi t0, " << destReg << ", -1" << std::endl;
            stream << "sw t0, " << symbol.offset << "(s0)" << std::endl;
        }
        else if (symbol.type == TypeSpecifier::FLOAT)
        {
            stream << "flw " << destReg << ", " << symbol.offset << "(s0)" << std::endl;
            stream << "fadd.s ft0, " << destReg << ", -1" << std::endl;
            stream << "fsw ft0, " << symbol.offset << "(s0)" << std::endl;
        }
        else if (symbol.type == TypeSpecifier::DOUBLE)
        {
            stream << "fld " << destReg << ", " << symbol.offset << "(s0)" << std::endl;
            stream << "fadd.d ft0, " << destReg << ", -1" << std::endl;
            stream << "fsd ft0, " << symbol.offset << "(s0)" << std::endl;
        }
        else
        {
            throw std::runtime_error("VariablePostInc: TypeSpecifier not supported");
        }
    }

    void VariablePostDec::Print(std::ostream& stream) const
    {
        stream << identifier_;
        stream << "--";
    }

} // namespace ast
