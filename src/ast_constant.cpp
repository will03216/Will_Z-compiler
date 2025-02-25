#include "ast_constant.hpp"

namespace ast {

    void IntConstant::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
{
    (void)context;
    stream << "li "<< destReg <<", " << value_ << std::endl;
}

void IntConstant::Print(std::ostream& stream) const
{
    stream << value_;
}

} // namespace ast
