#include "ast_symbol_table.hpp"

namespace ast {
    int SymbolTable::AddSymbol(const std::string& name, const TypeSpecifier& type)
    {
        table_[name] = {name, type, offset_};
        int temp = offset_;
        offset_ -= 4;
        return temp;
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
    int SymbolTable::GetOffset() const
    {
        return offset_;
    }
}// namespace ast
