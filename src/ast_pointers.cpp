#include "ast_pointers.hpp"

namespace ast {

void AddressOfExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
{
    expr_->EmitValueRISC(stream, context, destReg);
}

void AddressOfExpr::Print(std::ostream& stream) const
{
    stream << "&";
    expr_->Print(stream);
}

void DereferenceExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
{
    expr_->EmitRISC(stream, context, destReg, type);
    TypeSpecifier exprType = expr_->GetType(context);
    if (exprType == TypeSpecifier::INT)
    {
        stream << "lw " << destReg << ", 0(" << destReg << ")" << std::endl;
    }
    else if (exprType == TypeSpecifier::FLOAT)
    {
        stream << "flw f" << destReg << ", 0(" << destReg << ")" << std::endl;
    }
    else if (exprType == TypeSpecifier::DOUBLE)
    {
        stream << "fld f" << destReg << ", 0(" << destReg << ")" << std::endl;
    }
    else
    {
        throw std::runtime_error("DereferenceExpr::EmitRISC: invalid type");
    }
}

void DereferenceExpr::Print(std::ostream& stream) const
{
    stream << "*";
    expr_->Print(stream);
}

void DereferenceExpr::EmitValueRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
{
    expr_->EmitRISC(stream, context, destReg, TypeSpecifier::INT);
}


} // namespace ast
