#include "ast_enum.hpp"

namespace ast {

    void EnumMember::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const {
        (void)stream;
        (void)context;
        (void)destReg;
        (void)type;
    }

    void EnumMember::Print(std::ostream& stream) const {
        stream << identifier_;
        if (value_) {
            stream << " = ";
            value_->Print(stream);
        }
    }

    void EnumSpecifier::EmitRISC(std::ostream& , std::shared_ptr<Context> context, std::string , TypeSpecifier ) const {
        std::vector<Symbol> symbols = members_->GetSymbols(context);
        std::vector<std::variant<int, float, double>> consts = members_->GetConstList();
        int value = 0;
        for (size_t i = 0; i < symbols.size(); i++) {
            if (symbols[i].isPointer) {
                value = std::get<int>(consts[i]);
            }
            context->AddSymbol(symbols[i].name, TypeSpecifier::ENUM, value);
            value++;
        }
    }

    void EnumSpecifier::Print(std::ostream& stream) const {
        stream << "enum " << identifier_ << " {";
        members_->Print(stream);
        stream << "}";
    }

}// namespace ast
