#include "ast_string.hpp"

namespace ast {

    void StringLiteral::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
    {
        // Load the address of the string into the destination register
        int label = context->AddString(value_);
        stream << "la " << destReg << ", str_" << label << std::endl;

    }

    void StringLiteral::Print(std::ostream& stream) const
    {
        stream << value_;
    }

    std::vector<std::variant<int, float, double>> StringLiteral::GetConstList() const
    {
        std::vector<std::variant<int, float, double>> constList;
        for (char c : value_)
        {
            int val = static_cast<int>(c);
            constList.push_back(val);
        }
        return constList;
    }

} // namespace ast
