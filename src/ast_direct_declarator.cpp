#include "ast_direct_declarator.hpp"
#include <string>
namespace ast {

void DirectDeclarator::EmitRISC(std::ostream& stream,  std::shared_ptr<Context> context) const
{
    if (parameters_ != nullptr)
    {
        std::vector<std::string> identifiers = parameters_->GetIdentifiers();
        int index = 0;
        for (const auto& identifier : identifiers)
        {
            context->AddSymbol(identifier,  TypeSpecifier::INT); //TODO Fix type
            int offset = context->GetSymbol(identifier)->offset;
            stream << "sw a"<< index <<", " << offset << "(s0)" << std::endl;
            index++;
        }
    }

}

void DirectDeclarator::Print(std::ostream& stream) const
{
    identifier_->Print(stream);
}

} // namespace ast
