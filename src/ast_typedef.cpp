#include "ast_typedef.hpp"

namespace ast {

void TypedefDeclare::EmitRISC(std::ostream& , std::shared_ptr<Context> context, std::string , TypeSpecifier ) const
{
    context->AddType(declarator_->GetIdentifier(), declaration_specifiers_->GetType(context), 0, declarator_->IsPointer(context));
}

void TypedefDeclare::Print(std::ostream& stream) const
{
    declaration_specifiers_->Print(stream);
    stream << " ";
    declarator_->Print(stream);
    stream << ";\n";
}

} // namespace ast
