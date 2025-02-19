#include "ast_context.hpp"

namespace ast {
    void Context::AddSymbol(const std::string& name, const TypeSpecifier& type)
    {
        symbol_table_.AddSymbol(name, type);
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
}
