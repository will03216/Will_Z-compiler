#include "ast_arithmetic_operation.hpp"

namespace ast {

void AddExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context , std::string destReg, TypeSpecifier ) const
{
    TypeSpecifier lhs_type = lhs_->GetType(context);
    TypeSpecifier rhs_type = rhs_->GetType(context);
    TypeSpecifier result_type = CalculateType(lhs_type, rhs_type);

    int isPointer_left = lhs_->IsPointer(context);
    int isPointer_right = rhs_->IsPointer(context);


    if (isPointer_left == 1 && isPointer_right == 1)
    {
        throw std::runtime_error("Two pointers cannot be added together");
    }
    else if (isPointer_left == 1)
    {
        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw a4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "lw a4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        if (lhs_type == TypeSpecifier::INT || lhs_type == TypeSpecifier::FLOAT)
        {
            stream << "slli a5, a5, 2" << std::endl;
        }
        else if (lhs_type == TypeSpecifier::DOUBLE)
        {
            stream << "slli a5, a5, 3" << std::endl;
        }
        else if (lhs_type == TypeSpecifier::CHAR)
        {
            stream << "slli a5, a5, 0" << std::endl;
        }
        stream << "add "<< destReg <<",a4,a5" << std::endl;
        return;
    }
    else if (isPointer_right == 1)
    {
        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw a4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "lw a4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        if (lhs_type == TypeSpecifier::INT || lhs_type == TypeSpecifier::FLOAT)
        {
            stream << "slli a4, a4, 2" << std::endl;
        }
        else if (lhs_type == TypeSpecifier::DOUBLE)
        {
            stream << "slli a4, a4, 3" << std::endl;
        }
        else if (lhs_type == TypeSpecifier::CHAR)
        {
            stream << "slli a4, a4, 0" << std::endl;
        }
        stream << "add "<< destReg <<",a4,a5" << std::endl;
        return;
    }

    if (result_type == TypeSpecifier::FLOAT)
    {
        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "fsw fa4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "flw fa4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        stream << "fadd.s f"<< destReg <<",fa4,fa5" << std::endl;
        return;
    }
    else if (result_type == TypeSpecifier::DOUBLE)
    {
        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -8" << std::endl;
        stream << "fsd fa4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "fld fa4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 8" << std::endl;
        stream << "fadd.d f"<< destReg <<",fa4,fa5" << std::endl;
        return;
    }
    else if (result_type == TypeSpecifier::INT || result_type == TypeSpecifier::CHAR)
    {
        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw a4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "lw a4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        stream << "add "<< destReg <<",a4,a5" << std::endl;
        return;
    }
    else
    {
        throw std::runtime_error("Unexpected type specifier");
    }
}

void AddExpr::Print(std::ostream& stream) const
{
    stream << "add lhs + rhs";
}

void SubExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
{
    {
        TypeSpecifier lhs_type = lhs_->GetType(context);
        TypeSpecifier rhs_type = rhs_->GetType(context);
        TypeSpecifier result_type = CalculateType(lhs_type, rhs_type);

        int isPointer_left = lhs_->IsPointer(context);
        int isPointer_right = rhs_->IsPointer(context);


        if (isPointer_left == 1 && isPointer_right == 1)
        {
            lhs_->EmitRISC(stream, context, "a4", result_type);
            stream << "addi sp, sp, -4" << std::endl;
            stream << "sw a4, 0(sp)" << std::endl;
            rhs_->EmitRISC(stream, context, "a5", result_type);
            stream << "lw a4, 0(sp)" << std::endl;
            stream << "addi sp, sp, 4" << std::endl;
            stream << "sub "<< destReg <<",a4,a5" << std::endl;
            if (lhs_type == TypeSpecifier::INT || lhs_type == TypeSpecifier::FLOAT)
            {
                stream << "srli "<< destReg <<","<< destReg <<",2" << std::endl;
            }
            else if (lhs_type == TypeSpecifier::DOUBLE)
            {
                stream << "srli "<< destReg <<","<< destReg <<",3" << std::endl;
            }
            else if (lhs_type == TypeSpecifier::CHAR)
            {
                //can remove these
                stream << "srli "<< destReg <<","<< destReg <<",0" << std::endl;
            }
            return;
        }
        else if (isPointer_left == 1)
        {
            lhs_->EmitRISC(stream, context, "a4", result_type);
            stream << "addi sp, sp, -4" << std::endl;
            stream << "sw a4, 0(sp)" << std::endl;
            rhs_->EmitRISC(stream, context, "a5", result_type);
            stream << "lw a4, 0(sp)" << std::endl;
            stream << "addi sp, sp, 4" << std::endl;
            if (lhs_type == TypeSpecifier::INT || lhs_type == TypeSpecifier::FLOAT)
            {
                stream << "slli a5, a5, 2" << std::endl;
            }
            else if (lhs_type == TypeSpecifier::DOUBLE)
            {
                stream << "slli a5, a5, 3" << std::endl;
            }
            else if (lhs_type == TypeSpecifier::CHAR)
            {
                stream << "slli a5, a5, 0" << std::endl;
            }
            stream << "sub "<< destReg <<",a4,a5" << std::endl;
            return;
        }
        else if (isPointer_right == 1)
        {
            lhs_->EmitRISC(stream, context, "a4", result_type);
            stream << "addi sp, sp, -4" << std::endl;
            stream << "sw a4, 0(sp)" << std::endl;
            rhs_->EmitRISC(stream, context, "a5", result_type);
            stream << "lw a4, 0(sp)" << std::endl;
            stream << "addi sp, sp, 4" << std::endl;
            if (lhs_type == TypeSpecifier::INT || lhs_type == TypeSpecifier::FLOAT)
            {
                stream << "slli a4, a4, 2" << std::endl;
            }
            else if (lhs_type == TypeSpecifier::DOUBLE)
            {
                stream << "slli a4, a4, 3" << std::endl;
            }
            else if (lhs_type == TypeSpecifier::CHAR)
            {
                stream << "slli a4, a4, 0" << std::endl;
            }
            stream << "sub "<< destReg <<",a4,a5" << std::endl;
            return;
        }

        if (result_type == TypeSpecifier::FLOAT)
        {
            lhs_->EmitRISC(stream, context, "a4", result_type);
            stream << "addi sp, sp, -4" << std::endl;
            stream << "fsw fa4, 0(sp)" << std::endl;
            rhs_->EmitRISC(stream, context, "a5", result_type);
            stream << "flw fa4, 0(sp)" << std::endl;
            stream << "addi sp, sp, 4" << std::endl;
            stream << "fsub.s f"<< destReg <<",fa4,fa5" << std::endl;
            return;
        }
        else if (result_type == TypeSpecifier::DOUBLE)
        {
            lhs_->EmitRISC(stream, context, "a4", result_type);
            stream << "addi sp, sp, -8" << std::endl;
            stream << "fsd fa4, 0(sp)" << std::endl;
            rhs_->EmitRISC(stream, context, "a5", result_type);
            stream << "fld fa4, 0(sp)" << std::endl;
            stream << "addi sp, sp, 8" << std::endl;
            stream << "fsub.d f"<< destReg <<",fa4,fa5" << std::endl;
            return;
        }
        else if (result_type == TypeSpecifier::INT|| result_type == TypeSpecifier::CHAR)
        {
            lhs_->EmitRISC(stream, context, "a4", result_type);
            stream << "addi sp, sp, -4" << std::endl;
            stream << "sw a4, 0(sp)" << std::endl;
            rhs_->EmitRISC(stream, context, "a5", result_type);
            stream << "lw a4, 0(sp)" << std::endl;
            stream << "addi sp, sp, 4" << std::endl;
            stream << "sub "<< destReg <<",a4,a5" << std::endl;
            return;
        }
        else
        {
            throw std::runtime_error("Unexpected type specifier");
        }
    }
}

void SubExpr::Print(std::ostream& stream) const
{
    stream << "sub lhs - rhs";
}

void MulExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
{
    TypeSpecifier lhs_type = lhs_->GetType(context);
    TypeSpecifier rhs_type = rhs_->GetType(context);
    TypeSpecifier result_type = CalculateType(lhs_type, rhs_type);

    if (result_type == TypeSpecifier::FLOAT)
    {
        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "fsw fa4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "flw fa4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        stream << "fmul.s f"<< destReg <<",fa4,fa5" << std::endl;
        return;
    }
    else if (result_type == TypeSpecifier::DOUBLE)
    {
        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -8" << std::endl;
        stream << "fsd fa4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "fld fa4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 8" << std::endl;
        stream << "fmul.d f"<< destReg <<",fa4,fa5" << std::endl;
        return;
    }
    else if (result_type == TypeSpecifier::INT || result_type == TypeSpecifier::CHAR)
    {
        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw a4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "lw a4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        stream << "mul "<< destReg <<",a4,a5" << std::endl;
        return;
    }
    else
    {
        throw std::runtime_error("Unexpected type specifier");
    }
}

void MulExpr::Print(std::ostream& stream) const
{
    stream << "mul lhs * rhs";
}

void DivExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
{
    TypeSpecifier lhs_type = lhs_->GetType(context);
    TypeSpecifier rhs_type = rhs_->GetType(context);
    TypeSpecifier result_type = CalculateType(lhs_type, rhs_type);

    if (result_type == TypeSpecifier::FLOAT)
    {
        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "fsw fa4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "flw fa4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        stream << "fdiv.s f"<< destReg <<",fa4,fa5" << std::endl;
        return;
    }
    else if (result_type == TypeSpecifier::DOUBLE)
    {
        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -8" << std::endl;
        stream << "fsd fa4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "fld fa4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 8" << std::endl;
        stream << "fdiv.d f"<< destReg <<",fa4,fa5" << std::endl;
        return;
    }
    else if (result_type == TypeSpecifier::INT || result_type == TypeSpecifier::CHAR)
    {
        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw a4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "lw a4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        stream << "div "<< destReg <<",a4,a5" << std::endl;
        return;
    }
    else
    {
        throw std::runtime_error("Unexpected type specifier");
    }
}

void DivExpr::Print(std::ostream& stream) const
{
    stream << "div lhs / rhs";
}

void ModExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
{
    TypeSpecifier lhs_type = lhs_->GetType(context);
    TypeSpecifier rhs_type = rhs_->GetType(context);
    TypeSpecifier result_type = CalculateType(lhs_type, rhs_type);

    if (result_type == TypeSpecifier::INT || result_type == TypeSpecifier::CHAR)
    {
        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw a4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "lw a4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        stream << "rem "<< destReg <<",a4,a5" << std::endl;
        return;
    }
    else
    {
        throw std::runtime_error("Unexpected type specifier");
    }
}

void ModExpr::Print(std::ostream& stream) const
{
    stream << "mod lhs % rhs";
}

void LeftShiftExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
{
    lhs_->EmitRISC(stream, context, "a4", type);
    stream << "addi sp, sp, -4" << std::endl;
    stream << "sw a4, 0(sp)" << std::endl;
    rhs_->EmitRISC(stream, context, "a5", type);
    stream << "lw a4, 0(sp)" << std::endl;
    stream << "addi sp, sp, 4" << std::endl;
    stream << "sll "<< destReg <<",a4,a5" << std::endl;
}

void LeftShiftExpr::Print(std::ostream& stream) const
{
    stream << "left shift lhs << rhs";
}

void RightShiftExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
{
    lhs_->EmitRISC(stream, context, "a4", type);
    stream << "addi sp, sp, -4" << std::endl;
    stream << "sw a4, 0(sp)" << std::endl;
    rhs_->EmitRISC(stream, context, "a5", type);
    stream << "lw a4, 0(sp)" << std::endl;
    stream << "addi sp, sp, 4" << std::endl;
    stream << "srl "<< destReg <<",a4,a5" << std::endl;
}

void RightShiftExpr::Print(std::ostream& stream) const
{
    stream << "right shift lhs >> rhs";
}


void Negation::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
{
    TypeSpecifier type = expression_->GetType(context);

    if (type == TypeSpecifier::FLOAT)
    {
        expression_->EmitRISC(stream, context, destReg, type);
        stream << "fneg.s f"<< destReg <<",f"<< destReg <<"" << std::endl;
        return;
    }
    else if (type == TypeSpecifier::DOUBLE)
    {
        expression_->EmitRISC(stream, context, destReg, type);
        stream << "fneg.d f"<< destReg <<",f"<< destReg <<"" << std::endl;
        return;
    }
    else if (type == TypeSpecifier::INT || type == TypeSpecifier::CHAR)
    {
        expression_->EmitRISC(stream, context, destReg, type);
        stream << "neg "<< destReg <<","<< destReg <<"" << std::endl;
        return;
    }
    else
    {
        throw std::runtime_error("Unexpected type specifier");
    }
}

void Negation::Print(std::ostream& stream) const {
    stream << "-expression" << std::endl;
}



} // namespace ast
