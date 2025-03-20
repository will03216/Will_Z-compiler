#include "ast_size.hpp"

namespace ast {

void SizeOfExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
{
    TypeSpecifier exprType = expr_->GetType(context);
    if (exprType == TypeSpecifier::INT)
    {
        stream << "li " << destReg << ", 4" << std::endl;
    }
    else if (exprType == TypeSpecifier::FLOAT)
    {
        stream << "li " << destReg << ", 4" << std::endl;
    }
    else if (exprType == TypeSpecifier::DOUBLE)
    {
        stream << "li " << destReg << ", 8" << std::endl;
    }
    else if (exprType == TypeSpecifier::CHAR)
    {
        stream << "li " << destReg << ", 1" << std::endl;
    }
    else
    {
        throw std::runtime_error("SizeOfExpr: TypeSpecifier not supported");
    }
}

void SizeOfExpr::Print(std::ostream& stream) const
{
    stream << "sizeof(";
    if (expr_ != nullptr)
    {
        expr_->Print(stream);
    }
    stream << ")";
}

}
