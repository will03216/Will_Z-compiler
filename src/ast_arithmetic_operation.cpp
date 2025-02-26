#include "ast_arithmetic_operation.hpp"

namespace ast {


    void AddExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context , std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "add "<< destReg <<",a4,a5" << std::endl;

    }

    void AddExpr::Print(std::ostream& stream) const
    {
        stream << "add lhs + rhs";
    }

    void SubExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "sub "<< destReg <<",a4,a5" << std::endl;

    }

    void SubExpr::Print(std::ostream& stream) const
    {
        stream << "sub lhs - rhs";
    }

    void MulExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "mul "<< destReg <<",a4,a5" << std::endl;

    }

    void MulExpr::Print(std::ostream& stream) const
    {
        stream << "mul lhs * rhs";
    }

    void DivExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "div "<< destReg <<",a4,a5" << std::endl;

    }

    void DivExpr::Print(std::ostream& stream) const
    {
        stream << "div lhs / rhs";
    }

    void ModExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "rem "<< destReg <<",a4,a5" << std::endl;

    }

    void ModExpr::Print(std::ostream& stream) const
    {
        stream << "mod lhs % rhs";
    }

    void LeftShiftExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "sll "<< destReg <<",a4,a5" << std::endl;
    }

    void LeftShiftExpr::Print(std::ostream& stream) const
    {
        stream << "left shift lhs << rhs";
    }

    void RightShiftExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "srl "<< destReg <<",a4,a5" << std::endl;
    }

    void RightShiftExpr::Print(std::ostream& stream) const
    {
        stream << "right shift lhs >> rhs";
    }


    void Negation::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        expression_->EmitRISC(stream, context, destReg);
        stream << "neg " << destReg << ", " << destReg << std::endl;
    }

    void Negation::Print(std::ostream& stream) const {
        stream << "-expression" << std::endl;
    }





    } // namespace ast
