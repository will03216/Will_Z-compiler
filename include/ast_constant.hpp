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
};

class FloatConstant : public Node
{
private:
    float value_;

public:
    FloatConstant(float value) : value_(value) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
};

class DoubleConstant : public Node
{
private:
    double value_;

public:
    DoubleConstant(double value) : value_(value) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
