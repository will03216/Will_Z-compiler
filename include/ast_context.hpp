#pragma once

#include <ast_symbol_table.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "ast_type_specifier.hpp"
#include "ast_reg_stack.hpp"
#include "ast_function_table.hpp"

namespace ast {
class Context : public std::enable_shared_from_this<Context>
{
private:
    std::shared_ptr<Context> parent_context_;
    SymbolTable symbol_table_;
    static int label_counter_ ;
    static std::unordered_map<std::string, std::vector<TypeSpecifier>> function_parameters_;
    std::string function_call_name_;
    std::string exit_label_;
    static FunctionTable function_table_;
    //reg stack not used
    RegStack reg_stack_;
    // Private constructor to enforce shared_ptr management
    explicit Context(std::shared_ptr<Context> parent_context = nullptr, int offset = -20, RegStack reg_stack = RegStack())
        : parent_context_(std::move(parent_context)), symbol_table_(SymbolTable(offset)), reg_stack_(reg_stack) {}

public:
    // Factory function to ensure Context is always created as a shared_ptr
    static std::shared_ptr<Context> Create(std::shared_ptr<Context> parent_context = nullptr, int offset = -20, RegStack reg_stack = RegStack())
    {
        return std::shared_ptr<Context>(new Context(std::move(parent_context), offset, reg_stack));
    }
    // Adds a symbol to the current context.
    int AddSymbol(const std::string& name, const TypeSpecifier& type, int isPointer = 0);
    // Returns the symbol with the given name in the current context.
    const Symbol* GetSymbol(const std::string& name) const;
    // Checks if a symbol with the given name exists in the current context.
    bool HasSymbol(const std::string& name) const;
    // Creates a child context with a reference to the current context.
    std::shared_ptr<Context> CreateChildContext()
    {

        int offset = symbol_table_.GetOffset();
        RegStack reg_stack = reg_stack_;
        return Create(shared_from_this(), offset, reg_stack);
    }
    // Searches for a symbol in the current context and then in parent contexts.
    const Symbol* GetScopedSymbol(const std::string& name) const;
    std::string GetNewLabel();

    void AddArray(const std::string& name, const TypeSpecifier& type, int size) {
        symbol_table_.AddArray(name, type, size);
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

    void PushReg(std::ostream& stream, std::string reg, int offset) {
        reg_stack_.PushReg(reg, offset);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw " << reg << ", 0(sp)" << std::endl;
    }

    Reg PopReg(std::ostream& stream) {
        stream << "lw " << reg_stack_.TopReg().reg << ", 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        return reg_stack_.PopReg();
    }

    void ExitRegStack(std::ostream& stream) {
        while (!reg_stack_.Empty()) {
            stream << "lw " << reg_stack_.TopReg().reg << ", 0(sp)" << std::endl;
            stream << "addi sp, sp, 4" << std::endl;
            reg_stack_.PopReg();
        }
    }

    void AddFunction(const std::string& name, const TypeSpecifier& return_type, const std::vector<TypeSpecifier>& parameters)
    {
        function_table_.AddFunction(name, return_type, parameters);
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

    ~Context() = default;
};

} // namespace ast
