#pragma once

#include <unordered_map>
#include <string>
#include <ast_type_specifier.hpp>

namespace ast {

struct Symbol {
    std::string name;
    TypeSpecifier type;
    int offset;  // Stack offset for local variables

    // For implementation of global variables TODO
    //bool isGlobal;
};

class SymbolTable
{
    private:
        std::unordered_map<std::string, Symbol> table_;
        int offset_ = -20;
    public:

        SymbolTable(int offset = -20) : offset_(offset) {}
        int AddSymbol(const std::string& name, const TypeSpecifier& type); // change this to return offset so dont hv to call GetOffset on declaration

        const Symbol* GetSymbol(const std::string& name) const;
        bool HasSymbol(const std::string& name) const;
        int GetOffset() const;
        int AddArray(const std::string& name, const TypeSpecifier& type, int size);

};

} // namespace ast
