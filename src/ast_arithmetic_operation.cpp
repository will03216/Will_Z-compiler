#include "ast_arithmetic_operation.hpp"

namespace ast {


void AddExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
{
    lhs_->EmitRISC(stream, context);
    stream << "mv a4,a5" << std::endl;
    rhs_->EmitRISC(stream, context);
    stream << "add a5,a4,a5" << std::endl;
}

void AddExpr::Print(std::ostream& stream) const
{
    stream << "add lhs + rhs";
}

void SubExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
{
    lhs_->EmitRISC(stream, context);
    stream << "mv a4,a5"<< std::endl;
    rhs_->EmitRISC(stream, context);
    stream << "sub a5,a4,a5" << std::endl;
}

void SubExpr::Print(std::ostream& stream) const
{
    stream << "sub lhs - rhs";
}

}
