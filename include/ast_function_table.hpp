#include "ast_type_specifier.hpp"
#include "ast_reg_stack.hpp"

namespace ast {

struct Function {
    std::string name;
    TypeSpecifier return_type;
    std::vector<TypeSpecifier> parameters;
    int is_pointer;
    RegStack reg_stack = RegStack();
};

class FunctionTable {
private:
    std::unordered_map<std::string, Function> functions;
    std::string current_function;

public:
    void AddFunction(const std::string& name, const TypeSpecifier& return_type, const std::vector<TypeSpecifier>& parameters, int is_pointer)
    {
        functions[name] = Function{name, return_type, parameters, is_pointer};
    }

    void SetCurrentFunction(const std::string& name)
    {
        current_function = name;
    }

    const Function* GetCurrentFunction() const
    {
        return &functions.at(current_function);
    }

    const Function* GetFunction(const std::string& name) const
    {
        return &functions.at(name);
    }

    bool HasFunction(const std::string& name) const
    {
        return functions.find(name) != functions.end();
    }

    void PushReg(std::string reg, std::ostream& stream)
    {
        functions.at(current_function).reg_stack.PushReg(reg, stream);
    }

    void PopReg(std::ostream& stream)
    {
        return functions.at(current_function).reg_stack.PopReg(stream);
    }

    void ExitRegStack(std::ostream& stream)
    {
        functions.at(current_function).reg_stack.ExitRegStack(stream);
    }
};
} // namespace ast
