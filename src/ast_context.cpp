#include "ast_context.hpp"

namespace ast {
    int Context::label_counter_ = 1;
    FunctionTable Context::function_table_ = FunctionTable();
    LiteralTable Context::literal_table_ = LiteralTable();
    std::string Context::exit_label_ = "exit";
    int Context::AddSymbol(const std::string& name, const TypeSpecifier& type, int isPointer)
    {
        return symbol_table_.AddSymbol(name, type, isPointer);
    }
    const Symbol* Context::GetSymbol(const std::string& name) const
    {
        return symbol_table_.GetSymbol(name);
    }
    bool Context::HasSymbol(const std::string& name) const
    {
        return symbol_table_.HasSymbol(name);
    }
    const Symbol* Context::GetScopedSymbol(const std::string& name) const //11111
    {
        if (symbol_table_.HasSymbol(name))
        {
            return symbol_table_.GetSymbol(name);
        }
        if (parent_context_ == nullptr)
        {
            throw std::runtime_error("Symbol not found");
            return nullptr;
        }
        return parent_context_->GetScopedSymbol(name);
    }
    std::string Context::GetNewLabel()
    {
        return "L" + std::to_string(label_counter_++);
    }
}
