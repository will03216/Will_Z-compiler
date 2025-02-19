#include "ast_function_definition.hpp"

namespace ast {

void FunctionDefinition::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
{
    // Emit assembler directives.
    // TODO: these are just examples ones, make sure you understand
    // the concept of directives and correct them.
    stream << ".align 2" << std::endl;
    stream << ".text" << std::endl;
    stream << ".globl f" << std::endl;

    //enter scope of function
    std::shared_ptr<Context> function_context = context->CreateChildContext();
    //function label
    stream<< declarator_->GetIdentifier();
    stream << ":" << std::endl;
    //enter scope of function
    enter_scope(stream);

    //store function arguments
    if (declarator_ != nullptr)
    {
        declarator_->EmitRISC(stream, function_context);
    }

    if (compound_statement_ != nullptr)
    {
        compound_statement_->EmitRISC(stream, function_context);
    }
}

void FunctionDefinition::Print(std::ostream& stream) const
{
    stream << declaration_specifiers_ << " ";

    declarator_->Print(stream);
    stream << "() {" << std::endl;

    if (compound_statement_ != nullptr)
    {
        compound_statement_->Print(stream);
    }
    stream << "}" << std::endl;
}

}
