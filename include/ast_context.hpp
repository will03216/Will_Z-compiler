#pragma once

#include <ast_symbol_table.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "ast_type_specifier.hpp"

namespace ast {
class Context : public std::enable_shared_from_this<Context>
{
private:
    std::shared_ptr<Context> parent_context_;
    SymbolTable symbol_table_;
    static int label_counter_ ;
    static std::unordered_map<std::string, std::vector<TypeSpecifier>> function_parameters_;
    std::string function_call_name_;
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
    void AddFunction(const std::string& name, const std::vector<TypeSpecifier>& parameters) {
        function_parameters_[name] = parameters;
    }

    const std::vector<TypeSpecifier>& GetFunctionParameters(const std::string& name) {
        return function_parameters_[name];
    }

    void SetFunctionCallName(const std::string& name) {
        function_call_name_ = name;
    }

    const std::string& GetFunctionCallName() const {
        return function_call_name_;
    }

    ~Context() = default;
};

} // namespace ast
