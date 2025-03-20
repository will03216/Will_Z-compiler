#include "ast_bitwise_operation.hpp"

namespace ast {
    void BitwiseAndExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if (type == TypeSpecifier::INT || type == TypeSpecifier::CHAR)
        {
            lhs_->EmitRISC(stream, context, "a4", type);
            stream << "addi sp, sp, -4" << std::endl;
            stream << "sw a4, 0(sp)" << std::endl;
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "lw a4, 0(sp)" << std::endl;
            stream << "addi sp, sp, 4" << std::endl;
            stream << "and "<< destReg <<",a4,a5" << std::endl;
        }
        else
        {
            throw std::runtime_error("BitwiseAndExpr: TypeSpecifier not supported");
        }


    }
    void BitwiseAndExpr::Print(std::ostream& stream) const
    {
        stream << "and lhs & rhs";
    }

    void BitwiseInlcusiveOrExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if (type == TypeSpecifier::INT || type == TypeSpecifier::CHAR)
        {
            lhs_->EmitRISC(stream, context, "a4", type);
            stream << "addi sp, sp, -4" << std::endl;
            stream << "sw a4, 0(sp)" << std::endl;
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "lw a4, 0(sp)" << std::endl;
            stream << "addi sp, sp, 4" << std::endl;
            stream << "or "<< destReg <<",a4,a5" << std::endl;
        }
        else
        {
            throw std::runtime_error("BitwiseInlcusiveOrExpr: TypeSpecifier not supported");
        }
    }
    void BitwiseInlcusiveOrExpr::Print(std::ostream& stream) const
    {
        stream << "or lhs | rhs";
    }

    void BitwiseExclusiveOrExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if (type == TypeSpecifier::INT || type == TypeSpecifier::CHAR)
        {
            lhs_->EmitRISC(stream, context, "a4", type);
            stream << "addi sp, sp, -4" << std::endl;
            stream << "sw a4, 0(sp)" << std::endl;
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "lw a4, 0(sp)" << std::endl;
            stream << "addi sp, sp, 4" << std::endl;
            stream << "xor "<< destReg <<",a4,a5" << std::endl;
        }
        else
        {
            throw std::runtime_error("BitwiseExclusiveOrExpr: TypeSpecifier not supported");
        }
    }
    void BitwiseExclusiveOrExpr::Print(std::ostream& stream) const
    {
        stream << "xor lhs ^ rhs";
    }
}  // namespace ast
