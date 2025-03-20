#include "ast_function.hpp"


namespace ast {

void FunctionDefinition::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
{
    TypeSpecifier type = declaration_specifiers_->GetType(context);
    if ( compound_statement_ == nullptr)
    {
        context->AddFunction(declarator_->GetIdentifier(), type, declarator_->GetTypes(context), declarator_->IsPointer(context));
        return;
    }

    context->AddFunction(declarator_->GetIdentifier(), type, declarator_->GetTypes(context), declarator_->IsPointer(context));

    context->SetCurrentFunction(declarator_->GetIdentifier());


    std::string function_name = declarator_->GetIdentifier();
    // Emit assembler directives.
    // TODO: these are just examples ones, make sure you understand
    // the concept of directives and correct them.
    stream << ".align 2" << std::endl;
    stream << ".text" << std::endl;
    stream << ".globl "<< function_name << std::endl;



    std::shared_ptr<Context> function_context = context->CreateChildContext();

    //function label
    stream<< function_name << ":" << std::endl;

    //enter scope of function
    enter_scope(stream);

    //store function arguments
    if (declarator_ != nullptr)
    {
        declarator_->EmitRISC(stream, function_context, destReg, type);
    }

    if (compound_statement_ != nullptr)
    {
        std::string reg = "a5";
        compound_statement_->EmitRISC(stream, function_context, reg, type);
    }

    if (type == TypeSpecifier::VOID)
    {
        exit_scope(stream);
        stream << "ret" << std::endl;
    }

}

void FunctionDefinition::Print(std::ostream& stream) const
{

    declaration_specifiers_->Print(stream);
    stream << " ";

    declarator_->Print(stream);
    stream << "() {" << std::endl;

    if (compound_statement_ != nullptr)
    {
        compound_statement_->Print(stream);
    }
    stream << "}" << std::endl;

}

// need to handle this
void FunctionCall::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
{
    std::string function_name = identifier_->GetIdentifier();
    context->SetFunctionCallName(function_name);

    // Push S1 and S2 onto stack
    stream << "addi sp, sp, -8" << std::endl;
    stream << "sw s1, 0(sp)" << std::endl;
    stream << "sw s2, 4(sp)" << std::endl;


    stream << "mv s1, a4" << std::endl;
    stream << "mv s2, a5" << std::endl;
    if (argument_expression_list_ != nullptr) {
        argument_expression_list_->EmitRISC(stream, context, destReg, type);
    }
    stream << "call " << function_name << std::endl;
    stream << "mv a4, s1" << std::endl;
    stream << "mv a5, s2" << std::endl;

    // Pop S1 and S2 from stack
    stream << "lw s1, 0(sp)" << std::endl;
    stream << "lw s2, 4(sp)" << std::endl;
    stream << "addi sp, sp, 8" << std::endl;

    stream << "mv "<< destReg <<",a0" << std::endl;
}

void FunctionCall::Print(std::ostream& stream) const
{
    identifier_->Print(stream);
    stream << "(";
    if (argument_expression_list_ != nullptr)
    {
        argument_expression_list_->Print(stream);
    }
    stream << ")";

}




} // namespace ast
