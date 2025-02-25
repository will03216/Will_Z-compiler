#include "ast_init_declarator.hpp"
namespace ast {
    void InitDeclarator::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        if (initializer_ != nullptr)
        {
            initializer_->EmitRISC(stream, context, destReg);
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
