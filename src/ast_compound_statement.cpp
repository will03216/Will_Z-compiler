#include "ast_compound_statement.hpp"
#include "ast_context.hpp"
namespace ast {
void CompoundStatement::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
{
    std::shared_ptr<Context> inner_context = context->CreateChildContext();
    //enter_scope(stream);
    if (expression_ != nullptr)
    {
        expression_->EmitRISC(stream, inner_context);
    }
    //exit_scope(stream);
}
void CompoundStatement::Print(std::ostream& stream) const
{
    stream << "{" << std::endl;
    if (expression_ != nullptr)
    {
        expression_->Print(stream);
    }
    stream << "}" << std::endl;
}
}
