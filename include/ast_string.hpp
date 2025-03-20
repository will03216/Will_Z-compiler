#pragma once

#include "ast_node.hpp"

namespace ast {

class StringLiteral : public Node
{
private:
    std::string value_;

public:
    StringLiteral(std::string value) : value_(value) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier GetType(std::shared_ptr<Context>) const override { return TypeSpecifier::CHAR; }
    int IsPointer(std::shared_ptr<Context>) const override { return 0; }
    int IsArray() const override { return size(value_); }
    std::variant<int, float, double> GetConst() const override { return 0; }
    std::vector<std::variant<int, float, double>> GetConstList() const override;
};
} // namespace ast
