#include "ast_jump_statement.hpp"

namespace ast {

void ReturnStatement::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string, TypeSpecifier type) const
{
    //TypeSpecifier type = context->GetFunctionType();

    if(type == TypeSpecifier::INT){
        if (expression_ != nullptr)
        {
            expression_->EmitRISC(stream, context, "a5", type);
        }
        stream << "mv a0,a5" << std::endl;
        //context->ExitRegStack(stream);
        exit_scope(stream);
        stream << "ret" << std::endl;
    }
    else if (type == TypeSpecifier::FLOAT)
    {
        if (expression_ != nullptr)
        {
            expression_->EmitRISC(stream, context, "a5", type);
        }
        stream << "fmv.s fa0,fa5" << std::endl;
        //context->ExitRegStack(stream);
        exit_scope(stream);
        stream << "ret" << std::endl;
    }
    else if (type == TypeSpecifier::DOUBLE)
    {
        if (expression_ != nullptr)
        {
            expression_->EmitRISC(stream, context, "a5", type);
        }
        stream << "fmv.d fa0,fa5" << std::endl;
        //context->ExitRegStack(stream);
        exit_scope(stream);
        stream << "ret" << std::endl;
    }
    else if (type == TypeSpecifier::CHAR)
    {
        if (expression_ != nullptr)
        {
            expression_->EmitRISC(stream, context, "a5", type);
        }
        stream << "mv a0,a5" << std::endl;
        //context->ExitRegStack(stream);
        exit_scope(stream);
        stream << "ret" << std::endl;
    }
    else if (type == TypeSpecifier::VOID)
    {

        exit_scope(stream);
        stream << "ret" << std::endl;
    }
    else
    {
        throw std::runtime_error("ReturnStatement: TypeSpecifier not supported");
    }
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
