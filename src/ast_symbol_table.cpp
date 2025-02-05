#include "ast_symbol_table.hpp"

namespace ast {
    void SymbolTable::AddSymbol(const std::string& name, const std::string& type, int offset)
    {
        table_[name] = {name, type, offset};
    }
    const Symbol* SymbolTable::GetSymbol(const std::string& name) const
    {
        auto it = table_.find(name);
        if (it == table_.end())
        {
            return nullptr;
        }
        return &it->second;
    }
    bool SymbolTable::HasSymbol(const std::string& name) const
    {
        return table_.find(name) != table_.end();
    }
}// namespace ast
