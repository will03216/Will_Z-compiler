#include "ast_symbol_table.hpp"

namespace ast {
    int SymbolTable::AddSymbol(const std::string& name, const TypeSpecifier& type, bool )
    {
        if (type == TypeSpecifier::INT)
        {
            table_[name] = {name, type, offset_, -1, false};
            int temp = offset_;
            offset_ -= 4;
            return temp;
        }
        else if (type == TypeSpecifier::FLOAT)
        {
            table_[name] = {name, type, offset_, -1, false};
            int temp = offset_;
            offset_ -= 4;
            return temp;
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            table_[name] = {name, type, offset_, -1, false};
            int temp = offset_;
            offset_ -= 8;
            return temp;
        }
        else
        {
            throw std::runtime_error("SymbolTable: TypeSpecifier not supported");
        }
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
    int SymbolTable::AddArray(const std::string& name, const TypeSpecifier& type, int size)
    {
        table_[name] = {name, type, offset_, -1, false};
        int temp = offset_;
        offset_ -= 4 * size;
        return temp;
    }
}// namespace ast
