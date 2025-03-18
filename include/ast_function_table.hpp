#include "ast_type_specifier.hpp"

namespace ast {

struct Function {
    std::string name;
    TypeSpecifier return_type;
    std::vector<TypeSpecifier> parameters;
};

class FunctionTable {
private:
    std::unordered_map<std::string, Function> functions;
    std::string current_function;

public:
    void AddFunction(const std::string& name, const TypeSpecifier& return_type, const std::vector<TypeSpecifier>& parameters)
    {
        functions[name] = Function{name, return_type, parameters};
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
};
} // namespace ast
