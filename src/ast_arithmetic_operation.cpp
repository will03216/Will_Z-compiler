#include "ast_arithmetic_operation.hpp"

namespace ast
{

    void AddExpr::EmitRISC(std::ostream &stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        // Check if storing a4 is the right thing to do
        if (type == TypeSpecifier::FLOAT)
        {
            lhs_->EmitRISC(stream, context, "fa4", type);
            stream << "addi sp, sp, -4" << std::endl;
            stream << "fsw fa4, 0(sp)" << std::endl;
            rhs_->EmitRISC(stream, context, "fa5", type);
            stream << "flw fa4, 0(sp)" << std::endl;
            stream << "addi sp, sp, 4" << std::endl;
            stream << "fadd.s " << destReg << ",fa4,fa5" << std::endl;
            return;
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            lhs_->EmitRISC(stream, context, "fa4", type);
            stream << "addi sp, sp, -4" << std::endl;
            stream << "fsw fa4, 0(sp)" << std::endl;
            rhs_->EmitRISC(stream, context, "fa5", type);
            stream << "flw fa4, 0(sp)" << std::endl;
            stream << "addi sp, sp, 4" << std::endl;
            stream << "fadd.d " << destReg << ",fa4,fa5" << std::endl;
            return;
        }
        else if (type == TypeSpecifier::INT)
        {
            lhs_->EmitRISC(stream, context, "a4", type);
            stream << "addi sp, sp, -4" << std::endl;
            stream << "sw a4, 0(sp)" << std::endl;
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "lw a4, 0(sp)" << std::endl;
            stream << "addi sp, sp, 4" << std::endl;
            stream << "add " << destReg << ",a4,a5" << std::endl;
            return;
        }
        else
        {
            throw std::runtime_error("Unexpected type specifier");
        }
    }

    void AddExpr::Print(std::ostream &stream) const
    {
        stream << "add lhs + rhs";
    }

    void SubExpr::EmitRISC(std::ostream &stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if (type == TypeSpecifier::FLOAT)
        {
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
            stream << "fsub.s " << destReg << ",fa4,fa5" << std::endl;
            return;
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
            stream << "fsub.d " << destReg << ",fa4,fa5" << std::endl;
            return;
        }
        else if (type == TypeSpecifier::INT)
        {
            lhs_->EmitRISC(stream, context, "a4", type);
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "sub " << destReg << ",a4,a5" << std::endl;
            return;
        }
        else
        {
            throw std::runtime_error("Unexpected type specifier");
        }
    }
    void SubExpr::Print(std::ostream &stream) const
    {
        stream << "sub lhs - rhs";
    }

    void MulExpr::EmitRISC(std::ostream &stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if (type == TypeSpecifier::FLOAT)
        {
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
            stream << "fmul.s " << destReg << ",fa4,fa5" << std::endl;
            return;
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
            stream << "fmul.d " << destReg << ",fa4,fa5" << std::endl;
            return;
        }
        else if (type == TypeSpecifier::INT)
        {
            lhs_->EmitRISC(stream, context, "a4", type);
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "mul " << destReg << ",a4,a5" << std::endl;
            return;
        }
        else
        {
            throw std::runtime_error("Unexpected type specifier");
        }
    }

    void MulExpr::Print(std::ostream &stream) const
    {
        stream << "mul lhs * rhs";
    }

    void DivExpr::EmitRISC(std::ostream &stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if (type == TypeSpecifier::FLOAT)
        {
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
            stream << "fdiv.s " << destReg << ",fa4,fa5" << std::endl;
            return;
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
            stream << "fdiv.d " << destReg << ",fa4,fa5" << std::endl;
            return;
        }
        else if (type == TypeSpecifier::INT)
        {
            lhs_->EmitRISC(stream, context, "a4", type);
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "div " << destReg << ",a4,a5" << std::endl;
            return;
        }
        else
        {
            throw std::runtime_error("Unexpected type specifier");
        }
    }

    void DivExpr::Print(std::ostream &stream) const
    {
        stream << "div lhs / rhs";
    }

    void ModExpr::EmitRISC(std::ostream &stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if (type == TypeSpecifier::INT)
        {
            lhs_->EmitRISC(stream, context, "a4", type);
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "rem " << destReg << ",a4,a5" << std::endl;
            return;
        }
        else
        {
            throw std::runtime_error("Unexpected type specifier");
        }
    }

    void ModExpr::Print(std::ostream &stream) const
    {
        stream << "mod lhs % rhs";
    }

    void LeftShiftExpr::EmitRISC(std::ostream &stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        lhs_->EmitRISC(stream, context, "a4", type);
        rhs_->EmitRISC(stream, context, "a5", type);
        stream << "sll " << destReg << ",a4,a5" << std::endl;
    }

    void LeftShiftExpr::Print(std::ostream &stream) const
    {
        stream << "left shift lhs << rhs";
    }

    void RightShiftExpr::EmitRISC(std::ostream &stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        lhs_->EmitRISC(stream, context, "a4", type);
        rhs_->EmitRISC(stream, context, "a5", type);
        stream << "srl " << destReg << ",a4,a5" << std::endl;
    }

    void RightShiftExpr::Print(std::ostream &stream) const
    {
        stream << "right shift lhs >> rhs";
    }

    void Negation::EmitRISC(std::ostream &stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if (type == TypeSpecifier::FLOAT)
        {
            expression_->EmitRISC(stream, context, destReg, type);
            stream << "fneg.s " << destReg << "," << destReg << "" << std::endl;
            return;
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            expression_->EmitRISC(stream, context, destReg, type);
            stream << "fneg.d " << destReg << "," << destReg << "" << std::endl;
            return;
        }
        else if (type == TypeSpecifier::INT)
        {
            expression_->EmitRISC(stream, context, destReg, type);
            stream << "neg " << destReg << "," << destReg << "" << std::endl;
            return;
        }
        else
        {
            throw std::runtime_error("Unexpected type specifier");
        }
    }

    void Negation::Print(std::ostream &stream) const
    {
        stream << "-expression" << std::endl;
    }

} // namespace ast
