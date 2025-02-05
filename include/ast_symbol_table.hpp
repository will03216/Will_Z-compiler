#pragma once

#include <unordered_map>
#include <string>

namespace ast {

struct Symbol {
    std::string name;
    std::string type;
    int offset;  // Stack offset for local variables

    // For implementation of global variables TODO
    //bool isGlobal;
};

class SymbolTable
{
    private:
        std::unordered_map<std::string, Symbol> table_;
    public:
        void AddSymbol(const std::string& name, const std::string& type, int offset);
        const Symbol* GetSymbol(const std::string& name) const;
        bool HasSymbol(const std::string& name) const;
        //void Print(std::ostream& stream) const;
};

} // namespace ast
