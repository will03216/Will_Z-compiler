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
}
