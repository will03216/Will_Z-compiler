#pragma once

#include "ast_node.hpp"

namespace ast {

class IntConstant : public Node
{
private:
    int value_;

public:
    IntConstant(int value) : value_(value) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier GetType(std::shared_ptr<Context>) const override { return TypeSpecifier::INT; }
    int IsPointer(std::shared_ptr<Context>) const override { return 0; }
    std::variant<int, float, double> GetConst() const override { return value_; }
};

class FloatConstant : public Node
{
private:
    float value_;

public:
    FloatConstant(float value) : value_(value) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier GetType(std::shared_ptr<Context>) const override { return TypeSpecifier::FLOAT; }
    int IsPointer(std::shared_ptr<Context>) const override { return 0; }
    std::variant<int, float, double> GetConst() const override { return value_; }
};

class DoubleConstant : public Node
{
private:
    double value_;

public:
    DoubleConstant(double value) : value_(value) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier GetType(std::shared_ptr<Context>) const override { return TypeSpecifier::DOUBLE; }
    int IsPointer(std::shared_ptr<Context>) const override { return 0; }
    std::variant<int, float, double> GetConst() const override { return value_; }
};

} // namespace ast
