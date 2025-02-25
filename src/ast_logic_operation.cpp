#include "ast_logic_operation.hpp"

namespace ast {
    void LessThanExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "slt "<< destReg <<",a4,a5" << std::endl;
    }
    void LessThanExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " < ";
        rhs_->Print(stream);
        stream << ")";
    }

    void GreaterThanExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "sgt "<< destReg <<",a4,a5" << std::endl;
    }
    void GreaterThanExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " > ";
        rhs_->Print(stream);
        stream << ")";
    }

    void LessThanEqualExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "sgt "<< destReg <<",a4,a5" << std::endl;
        stream << "xori "<< destReg <<","<< destReg <<",1" << std::endl;
    }
    void LessThanEqualExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " <= ";
        rhs_->Print(stream);
        stream << ")";
    }

    void GreaterThanEqualExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");
        stream << "slt "<< destReg <<",a4,a5" << std::endl;
        stream << "xori "<< destReg <<","<< destReg <<",1" << std::endl;
    }
    void GreaterThanEqualExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " >= ";
        rhs_->Print(stream);
        stream << ")";
    }

    void EqualityExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");

        stream << "sub a5,a4,a5" << std::endl;
        stream << "seqz "<< destReg <<",a5" << std::endl;
    }

    void EqualityExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " == ";
        rhs_->Print(stream);
        stream << ")";
    }

    void InequalityExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        lhs_->EmitRISC(stream, context, "a4");
        rhs_->EmitRISC(stream, context, "a5");

        stream << "sub a5,a4,a5" << std::endl;
        stream << "seqz "<< destReg <<",a5" << std::endl;
    }

    void InequalityExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " != ";
        rhs_->Print(stream);
        stream << ")";
    }
    void LogicalAndExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        std::string logical_and_false = context->GetNewLabel();
        std::string end = context->GetNewLabel();

        lhs_->EmitRISC(stream, context, "a5");
        stream << "beqz a5, " << logical_and_false << std::endl;
        rhs_->EmitRISC(stream, context, "a5");
        stream << "beqz a5, " << logical_and_false << std::endl;
        stream << "li "<< destReg <<", 1" << std::endl;
        stream << "j " << end << std::endl;
        stream << logical_and_false << ":" << std::endl;
        stream << "li "<< destReg <<", 0" << std::endl;
        stream << end << ":" << std::endl;
        stream << ")";
    }
    void LogicalAndExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " && ";
        rhs_->Print(stream);
        stream << ")";
    }

    void LogicalOrExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
    {
        std::string logical_or_true = context->GetNewLabel();
        std::string logical_or_false = context->GetNewLabel();
        std::string end = context->GetNewLabel();

        lhs_->EmitRISC(stream, context, "a5");
        stream << "bnez a5, " << logical_or_true << std::endl;
        rhs_->EmitRISC(stream, context, "a5");
        stream << "beqz a5, " << logical_or_false << std::endl;
        stream << logical_or_true << ":" << std::endl;
        stream << "li "<< destReg <<", 1" << std::endl;
        stream << "j " << end << std::endl;
        stream << logical_or_false << ":" << std::endl;
        stream << "li "<< destReg <<", 0" << std::endl;
        stream << end << ":" << std::endl;
    }

    void LogicalOrExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " || ";
        rhs_->Print(stream);
        stream << ")";
    }
}
