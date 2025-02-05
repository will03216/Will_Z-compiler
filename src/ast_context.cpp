#include "ast_context.hpp"

namespace ast {
    void Context::AddSymbol(const std::string& name, const std::string& type, int offset)
    {
        symbol_table_.AddSymbol(name, type, offset);
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
