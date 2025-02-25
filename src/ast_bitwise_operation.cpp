#include "ast_bitwise_operation.hpp"

namespace ast {
    void BitwiseAndExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "and "<< destReg <<",a4,a5" << std::endl;

    }
    void BitwiseAndExpr::Print(std::ostream& stream) const
    {
        stream << "and lhs & rhs";
    }

    void BitwiseInlcusiveOrExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "or "<< destReg <<",a4,a5" << std::endl;

    }
    void BitwiseInlcusiveOrExpr::Print(std::ostream& stream) const
    {
        stream << "or lhs | rhs";
    }

    void BitwiseExclusiveOrExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "xor "<< destReg <<",a4,a5" << std::endl;

    }
    void BitwiseExclusiveOrExpr::Print(std::ostream& stream) const
    {
        stream << "xor lhs ^ rhs";
    }
}  // namespace ast
