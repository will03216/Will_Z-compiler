#pragma once

#include <ast_symbol_table.hpp>

namespace ast {
// An object of class Context is passed between ast nodes during compilation.
// This can be used to pass around information about what's currently being
// compiled (e.g. function scope and variable names).
class Context
{
    private:
        SymbolTable symbol_table_;

    public:
        void AddSymbol(const std::string& name, const std::string& type, int offset);
        const Symbol* GetSymbol(const std::string& name) const;
        bool HasSymbol(const std::string& name) const;
        //void Print(std::ostream& stream) const;
};

} // namespace ast
