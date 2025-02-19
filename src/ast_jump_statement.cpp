#include "ast_jump_statement.hpp"

namespace ast {

void ReturnStatement::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
{
    if (expression_ != nullptr)
    {
        expression_->EmitRISC(stream, context);
    }
    stream << "mv a0,a5" << std::endl;
    exit_scope(stream);
    stream << "ret" << std::endl;
}

void ReturnStatement::Print(std::ostream& stream) const
{
    stream << "return";
    if (expression_ != nullptr)
    {
        stream << " ";
        expression_->Print(stream);
    }
    stream << ";" << std::endl;
}

}
