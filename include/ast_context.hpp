#pragma once

#include <ast_symbol_table.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "ast_type_specifier.hpp"
#include "ast_reg_stack.hpp"
#include "ast_function_table.hpp"
#include "ast_literals.hpp"
#include "ast_struct_table.hpp"

namespace ast {

class Context : public std::enable_shared_from_this<Context>
{
private:
    std::shared_ptr<Context> parent_context_;
    SymbolTable symbol_table_;
    static int label_counter_ ;
    std::string function_call_name_;
    static std::string exit_label_;
    static FunctionTable function_table_;
    static LiteralTable literal_table_;
    StructTable struct_table_;


    // Private constructor to enforce shared_ptr management
    explicit Context(std::shared_ptr<Context> parent_context = nullptr, int offset = -20, StructTable struct_table = StructTable())
        : parent_context_(std::move(parent_context)), symbol_table_(SymbolTable(offset)), struct_table_(struct_table) {}

public:
    // Factory function to ensure Context is always created as a shared_ptr
    static std::shared_ptr<Context> Create(std::shared_ptr<Context> parent_context = nullptr, int offset = -20, StructTable struct_table = StructTable())
    {
        return std::shared_ptr<Context>(new Context(std::move(parent_context), offset, struct_table));
    }

    // Adds a symbol to the current context.
    int AddSymbol(const std::string& name, const TypeSpecifier& type, int isPointer = 0, int size = 0, std::string structIdentifier = "");

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

    // Returns a new label for the current context.
    std::string GetNewLabel();

    int AddArray(const std::string& name, const TypeSpecifier& type, int size) {
        return symbol_table_.AddArray(name, type, size);
    }

    void SetFunctionCallName(const std::string& name) {
        function_call_name_ = name;
    }

    const std::string& GetFunctionCallName() const {
        return function_call_name_;
    }

    void SetExitLabel(const std::string& label) {
        exit_label_ = label;
    }

    const std::string& GetExitLabel() const {
        return exit_label_;
    }

    void PushReg(std::string reg, std::ostream& stream) {
        function_table_.PushReg(reg, stream);
    }

    void PopReg(std::ostream& stream) {
        function_table_.PopReg(stream);
    }

    void ExitRegStack(std::ostream& stream) {
        function_table_.ExitRegStack(stream);
    }

    void AddFunction(const std::string& name, const TypeSpecifier& return_type, const std::vector<TypeSpecifier>& parameters, int is_pointer)
    {
        function_table_.AddFunction(name, return_type, parameters, is_pointer);
    }

    void SetCurrentFunction(const std::string& name)
    {
        function_table_.SetCurrentFunction(name);
    }

    const Function* GetCurrentFunction() const
    {
        return function_table_.GetCurrentFunction();
    }

    const Function* GetFunction(const std::string& name) const
    {
        return function_table_.GetFunction(name);
    }

    bool HasFunction(const std::string& name) const
    {
        return function_table_.HasFunction(name);
    }

    void ConstructLiterals(std::ostream& stream)
    {
        literal_table_.ConstructLiterals(stream);
    }

    int AddString(std::string value)
    {
        return literal_table_.AddString(value);
    }

    int GetStringLabel(std::string value)
    {
        return literal_table_.GetStringLabel(value);
    }

    void AddStruct(const std::string& identifier, const Struct& s)
    {
        struct_table_.AddStruct(identifier, s);
    }

    const Struct* GetStruct(const std::string& identifier) const
    {
        if (struct_table_.HasStruct(identifier))
            return struct_table_.GetStruct(identifier);
        else
            return parent_context_->GetStruct(identifier);
    }

    bool HasStruct(const std::string& identifier) const
    {
        return struct_table_.HasStruct(identifier);
    }

    StructMember GetMember(const std::string& struct_identifier, const std::string& member_identifier) const
    {
        if (struct_table_.HasStruct(struct_identifier))
        {
            return struct_table_.GetMember(struct_identifier, member_identifier);
        }
        else
        {
            return parent_context_->GetMember(struct_identifier, member_identifier);
        }

    }

    ~Context() = default;
};
}
