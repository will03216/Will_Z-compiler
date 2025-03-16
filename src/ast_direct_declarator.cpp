#include "ast_direct_declarator.hpp"
#include <string>
namespace ast {

    void DirectDeclarator::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string, TypeSpecifier ) const
    {

        if (is_array_ == -1)
        {
            if (parameters_ != nullptr)
        {
            std::vector<std::string> identifiers = parameters_->GetIdentifiers();
            std::vector<TypeSpecifier> types = parameters_->GetTypes();
            int index_int = 0;
            int index_float = 0;
            for (const auto& identifier : identifiers)
            {
                TypeSpecifier type = types[index_int + index_float];
                int offset = context->AddSymbol(identifier, type);
                if (type == TypeSpecifier::INT)
                {
                    stream << "sw a" << index_int << ", " << offset << "(s0)" << std::endl;
                    index_int++;
                }
                else if (type == TypeSpecifier::FLOAT)
                {
                    stream << "fsw fa" << index_float << ", " << offset << "(s0)" << std::endl;
                    index_float++;
                }
                else
                {
                    throw std::runtime_error("Unexpected type specifier");
                }
            }
        }
        } else {
            // parameter should always be nullptr if is_array_ is not -1
            if (parameters_ != nullptr){
                parameters_->EmitRISC(stream, context, "a5", TypeSpecifier::INT);
            }
        }
    }

void DirectDeclarator::Print(std::ostream& stream) const
{
    identifier_->Print(stream);
}

} // namespace ast
