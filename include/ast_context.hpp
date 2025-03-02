#pragma once

#include <ast_symbol_table.hpp>
#include <memory>
#include <string>

namespace ast {
class Context : public std::enable_shared_from_this<Context>
{
private:
    std::shared_ptr<Context> parent_context_;
    SymbolTable symbol_table_;
    static int label_counter_ ;
    // Private constructor to enforce shared_ptr management
    explicit Context(std::shared_ptr<Context> parent_context = nullptr, int offset = -20)
        : parent_context_(std::move(parent_context)), symbol_table_(SymbolTable(offset)) {}

public:
    // Factory function to ensure Context is always created as a shared_ptr
    static std::shared_ptr<Context> Create(std::shared_ptr<Context> parent_context = nullptr, int offset = -20)
    {
        return std::shared_ptr<Context>(new Context(std::move(parent_context), offset));
    }
    // Adds a symbol to the current context.
    int AddSymbol(const std::string& name, const TypeSpecifier& type);
    // Returns the symbol with the given name in the current context.
    const Symbol* GetSymbol(const std::string& name) const;
    // Checks if a symbol with the given name exists in the current context.
    bool HasSymbol(const std::string& name) const;
    // Creates a child context with a reference to the current context.
    std::shared_ptr<Context> CreateChildContext()
    {

        int offset = symbol_table_.GetOffset();
        return Create(shared_from_this(), offset);
    }
    // Searches for a symbol in the current context and then in parent contexts.
    const Symbol* GetScopedSymbol(const std::string& name) const;
    std::string GetNewLabel();

    void AddArray(const std::string& name, const TypeSpecifier& type, int size) {
        symbol_table_.AddArray(name, type, size);
    }
    ~Context() = default;
};

} // namespace ast
