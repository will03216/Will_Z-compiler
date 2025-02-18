#include "ast_init_declarator.hpp"
namespace ast {
    void InitDeclarator::EmitRISC(std::ostream& stream, Context& context) const
    {
        if (initializer_ != nullptr)
        {
            initializer_->EmitRISC(stream, context);
        }
    }
    void InitDeclarator::Print(std::ostream& stream) const
    {
        declarator_->Print(stream);
        if (initializer_ != nullptr)
        {
            stream << " = ";
            initializer_->Print(stream);
        }
    }
}
