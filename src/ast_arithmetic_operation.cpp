#include "ast_arithmetic_operation.hpp"

namespace ast {


void AddExpr::EmitRISC(std::ostream& stream, Context& context) const
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
}
