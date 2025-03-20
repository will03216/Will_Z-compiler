#include "ast_direct_declarator.hpp"
#include <string>

namespace ast {

void DirectDeclarator::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string, TypeSpecifier ) const
{
    if (is_array_ == -1)
    {
        if (parameters_ != nullptr)
    {

        std::vector<Symbol> symbols = parameters_->GetSymbols(context);
        std::vector<std::string> identifiers = parameters_->GetIdentifiers();
        std::vector<TypeSpecifier> types = parameters_->GetTypes(context);
        int index_int = 0;
        int index_float = 0;
        for (const auto& symbol : symbols)
        {
            TypeSpecifier type = symbol.type;
            std::string identifier = symbol.name;
            int isPointer = symbol.isPointer;
            // Add array support
            int offset = context->AddSymbol(identifier, type, isPointer);
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
            else if (type == TypeSpecifier::DOUBLE)
            {
                stream << "fsd fa" << index_float << ", " << offset << "(s0)" << std::endl;
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

void Declarator::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
{
    direct_declarator_->EmitRISC(stream, context, destReg, type);
}

void Declarator::Print(std::ostream& stream) const
{
    direct_declarator_->Print(stream);
}

} // namespace ast
