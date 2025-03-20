#include "ast_symbol_table.hpp"

namespace ast {
    int SymbolTable::AddSymbol(const std::string& name, const TypeSpecifier& type, int isPointer, int size, std::string structIdentifier)
    {
        if (type == TypeSpecifier::INT)
        {
            table_[name] = {name, type, offset_, -1, isPointer};
            int temp = offset_;
            offset_ -= 4;
            return temp;
        }
        else if (type == TypeSpecifier::FLOAT)
        {
            table_[name] = {name, type, offset_, -1, isPointer};
            int temp = offset_;
            offset_ -= 4;
            return temp;
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            table_[name] = {name, type, offset_, -1, isPointer};
            int temp = offset_;
            offset_ -= 8;
            return temp;
        }
        else if (type == TypeSpecifier::CHAR)
        {
            table_[name] = {name, type, offset_, -1, isPointer};
            int temp = offset_;
            offset_ -= 1;
            return temp;
        }
        else if (type == TypeSpecifier::STRUCT)
        {
            offset_ -= size;
            table_[name] = {structIdentifier, type, offset_, -1, isPointer};
            return offset_;
        }
        else if (type == TypeSpecifier::ENUM)
        {
            // Lazy implementation, change it later
            table_[name] = {name, type, isPointer, -1, isPointer};
            return isPointer;
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
        if (type == TypeSpecifier::INT || type == TypeSpecifier::FLOAT){
            offset_ -= 4 * size;
            table_[name] = {name, type, offset_ + 4, size, false};
            return offset_+4;
        }
        else if (type == TypeSpecifier::DOUBLE){
            offset_ -= 8 * size;
            table_[name] = {name, type, offset_ + 8, size, false};
            return offset_+8;
        }
        else if (type == TypeSpecifier::CHAR){
            offset_ -= size;
            table_[name] = {name, type, offset_ + 1, size, false};
            return offset_+1;
        }
        else
        {
            throw std::runtime_error("SymbolTable: TypeSpecifier not supported");
        }
    }

}// namespace ast
