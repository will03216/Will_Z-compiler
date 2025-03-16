#include "ast_constant.hpp"

namespace ast {

    void IntConstant::EmitRISC(std::ostream& stream, std::shared_ptr<Context> , std::string destReg, TypeSpecifier type) const
{
    if (type == TypeSpecifier::INT)
    {
        stream << "li "<< destReg <<", " << value_ << std::endl;
    }
    else if (type == TypeSpecifier::FLOAT)
    {
        stream << "li t0, " << value_ << std::endl;
        stream << "fcvt.s.w " << destReg << ", t0"<< std::endl;
    }
    else if (type == TypeSpecifier::DOUBLE)
    {
        stream << "li t0, " << value_ << std::endl;
        stream << "fcvt.s.w " << destReg << ", t0"<< std::endl;
    }
    else
    {
        throw std::runtime_error("IntConstant: TypeSpecifier not supported");
    }
}

void IntConstant::Print(std::ostream& stream) const
{
    stream << value_;
}

void FloatConstant::EmitRISC(std::ostream& stream, std::shared_ptr<Context> , std::string destReg, TypeSpecifier ) const
{
    stream << "li t0, " << value_ << std::endl;
    stream << "fcvt.s.w " << destReg << ", t0"<< std::endl;
}

void FloatConstant::Print(std::ostream& stream) const
{
    stream << value_;
}

void DoubleConstant::EmitRISC(std::ostream& stream, std::shared_ptr<Context> , std::string destReg, TypeSpecifier ) const
{
    stream << "li t0, " << value_ << std::endl;
    stream << "fcvt.s.w " << destReg << ", t0"<< std::endl;
}

void DoubleConstant::Print(std::ostream& stream) const
{
    stream << value_;
}

} // namespace ast
