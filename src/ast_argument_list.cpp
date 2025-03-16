#include "ast_argument_list.hpp"

namespace ast {
    void ArgumentExpressionList::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier) const
    {
        std::string function_name = context->GetFunctionCallName();
        std::vector<TypeSpecifier> parameters = context->GetFunctionParameters(function_name);
        bool is_external = false;

        if (parameters.size() == 0 && arguments_.size() != 0)
        {
            is_external = true;
        }

        //Temp fix for external functions (Ask about this)
        if (is_external)
        {
            int index = 0;
            for (const auto& argument : arguments_)
            {
                argument->EmitRISC(stream, context, destReg, TypeSpecifier::INT);
                stream << "mv a" << index << ", " << destReg << std::endl;
                index++;
            }
            return;
        }

        int index_int = 0;
        int index_float = 0;
    for (const auto& argument : arguments_)
    {
        TypeSpecifier type = parameters[index_int + index_float];
        argument->EmitRISC(stream, context, destReg, type);
        if (type == TypeSpecifier::INT)
        {
            stream << "mv a" << index_int << ", " << destReg << std::endl;
            index_int++;
        }
        else if (type == TypeSpecifier::FLOAT)
        {
            stream << "fmv.s fa" << index_float << ", " << destReg << std::endl;
            index_float++;
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            stream << "fmv.d fa" << index_float << ", " << destReg << std::endl;
            index_float++;
        }
        else
        {
            throw std::runtime_error("Unexpected type specifier");
        }
    }
}

void ArgumentExpressionList::Print(std::ostream& stream) const
{
    for (size_t i = 0; i < arguments_.size(); i++)
    {
        arguments_[i]->Print(stream);
        if (i != arguments_.size() - 1)
        {
            stream << ", ";
        }
    }
}

void ArgumentExpressionList::PushBack(NodePtr argument)
{
    arguments_.push_back(std::move(argument));
}
void Parameter::EmitRISC(std::ostream& , std::shared_ptr<Context> , std::string , TypeSpecifier ) const
{
    // do nothing
}

void Parameter::Print(std::ostream& stream) const
{
    stream << type_ << " " << identifier_->GetIdentifier();
}

std::string Parameter::GetIdentifier() const
{
    return identifier_->GetIdentifier();
}

TypeSpecifier Parameter::GetType() const
{
    return type_;
}

} // namespace ast


