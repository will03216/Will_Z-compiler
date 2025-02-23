#include "ast_argument_list.hpp"

namespace ast {
    void ArgumentExpressionList::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
{
    int num_args = 0;
    for (const auto& argument : arguments_)
    {
        argument->EmitRISC(stream, context);
        stream << "mv a" << num_args << ",a5" << std::endl;
        num_args++;
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

}
