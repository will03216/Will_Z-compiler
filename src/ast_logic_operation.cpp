#include "ast_logic_operation.hpp"

namespace ast {
    void LessThanExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg,  TypeSpecifier ) const
    {
        TypeSpecifier lhs_type = lhs_->GetType(context);
        TypeSpecifier rhs_type = rhs_->GetType(context);
        TypeSpecifier result_type = CalculateType(lhs_type, rhs_type);

        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw a4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "lw a4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        if (result_type == TypeSpecifier::INT)
        {
            stream << "slt "<< destReg <<",a4,a5" << std::endl;
        }
        else if (result_type == TypeSpecifier::FLOAT)
        {
            stream << "flt.s "<< destReg <<",fa4,fa5" << std::endl;
        }
        else if (result_type == TypeSpecifier::DOUBLE)
        {
            stream << "flt.d "<< destReg <<",fa4,fa5" << std::endl;
        }
        else
        {
            throw std::runtime_error("LessThanExpr: TypeSpecifier not supported");
        }
    }
    void LessThanExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " < ";
        rhs_->Print(stream);
        stream << ")";
    }

    void GreaterThanExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
    {
        TypeSpecifier lhs_type = lhs_->GetType(context);
        TypeSpecifier rhs_type = rhs_->GetType(context);
        TypeSpecifier result_type = CalculateType(lhs_type, rhs_type);

        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw a4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "lw a4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        if (result_type == TypeSpecifier::INT)
        {


            stream << "sgt "<< destReg <<",a4,a5" << std::endl;
        }
        else if (result_type == TypeSpecifier::FLOAT)
        {


            stream << "flt.s "<< destReg <<",fa4,fa5" << std::endl;
        }
        else if (result_type == TypeSpecifier::DOUBLE)
        {


            stream << "flt.d "<< destReg <<",fa4,fa5" << std::endl;
        }
        else
        {
            throw std::runtime_error("GreaterThanExpr: TypeSpecifier not supported");
        }
    }
    void GreaterThanExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " > ";
        rhs_->Print(stream);
        stream << ")";
    }

    void LessThanEqualExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
    {
        TypeSpecifier lhs_type = lhs_->GetType(context);
        TypeSpecifier rhs_type = rhs_->GetType(context);
        TypeSpecifier result_type = CalculateType(lhs_type, rhs_type);

        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw a4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "lw a4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        if (result_type == TypeSpecifier::INT)
        {


            stream << "sgt "<< destReg <<",a4,a5" << std::endl;
            stream << "xori "<< destReg <<","<< destReg <<",1" << std::endl;
        }
        else if (result_type == TypeSpecifier::FLOAT)
        {


            stream << "fle.s "<< destReg <<",fa4,fa5" << std::endl;
        }
        else if (result_type == TypeSpecifier::DOUBLE)
        {


            stream << "fle.d "<< destReg <<",fa4,fa5" << std::endl;
        }
        else
        {
            throw std::runtime_error("LessThanEqualExpr: TypeSpecifier not supported");
        }
    }
    void LessThanEqualExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " <= ";
        rhs_->Print(stream);
        stream << ")";
    }

    void GreaterThanEqualExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
    {
        TypeSpecifier lhs_type = lhs_->GetType(context);
        TypeSpecifier rhs_type = rhs_->GetType(context);
        TypeSpecifier result_type = CalculateType(lhs_type, rhs_type);

        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw a4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "lw a4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        if (result_type == TypeSpecifier::INT){
            stream << "slt "<< destReg <<",a4,a5" << std::endl;
            stream << "xori "<< destReg <<","<< destReg <<",1" << std::endl;
        }
        else if (result_type == TypeSpecifier::FLOAT)
        {


            stream << "fle.s "<< destReg <<",fa4,fa5" << std::endl;
        }
        else if (result_type == TypeSpecifier::DOUBLE)
        {


            stream << "fle.d "<< destReg <<",fa4,fa5" << std::endl;
        }
        else
        {
            throw std::runtime_error("GreaterThanEqualExpr: TypeSpecifier not supported");
        }
    }
    void GreaterThanEqualExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " >= ";
        rhs_->Print(stream);
        stream << ")";
    }

    void EqualityExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
    {
        TypeSpecifier lhs_type = lhs_->GetType(context);
        TypeSpecifier rhs_type = rhs_->GetType(context);
        TypeSpecifier result_type = CalculateType(lhs_type, rhs_type);

        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw a4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "lw a4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        if(result_type == TypeSpecifier::INT) {
            stream << "sub "<< destReg <<",a4,a5" << std::endl;
            stream << "seqz "<< destReg <<","<< destReg << std::endl;
        }
        else if(result_type == TypeSpecifier::FLOAT) {


            stream << "feq.s "<< destReg <<",fa4,fa5" << std::endl;
        }
        else if(result_type == TypeSpecifier::DOUBLE) {


            stream << "feq.d "<< destReg <<",fa4,fa5" << std::endl;
        }
        else {
            throw std::runtime_error("EqualityExpr: TypeSpecifier not supported");
        }
    }

    void EqualityExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " == ";
        rhs_->Print(stream);
        stream << ")";
    }

    void InequalityExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier ) const
    {
        TypeSpecifier lhs_type = lhs_->GetType(context);
        TypeSpecifier rhs_type = rhs_->GetType(context);
        TypeSpecifier result_type = CalculateType(lhs_type, rhs_type);

        lhs_->EmitRISC(stream, context, "a4", result_type);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw a4, 0(sp)" << std::endl;
        rhs_->EmitRISC(stream, context, "a5", result_type);
        stream << "lw a4, 0(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        if(result_type == TypeSpecifier::INT){
            stream << "sub "<< destReg <<",a4,a5" << std::endl;
            stream << "snez "<< destReg <<","<< destReg << std::endl;
        }
        else if(result_type == TypeSpecifier::FLOAT){


            stream << "fne.s "<< destReg <<",fa4,fa5" << std::endl;
        }
        else if(result_type == TypeSpecifier::DOUBLE){


            stream << "fne.d "<< destReg <<",fa4,fa5" << std::endl;
        }
        else{
            throw std::runtime_error("InequalityExpr: TypeSpecifier not supported");
        }
    }

    void InequalityExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " != ";
        rhs_->Print(stream);
        stream << ")";
    }

    void LogicalAndExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        std::string logical_and_false = context->GetNewLabel();
        std::string end = context->GetNewLabel();

        lhs_->EmitRISC(stream, context, "a5", type);
        stream << "beqz a5, " << logical_and_false << std::endl;
        rhs_->EmitRISC(stream, context, "a5", type);
        stream << "beqz a5, " << logical_and_false << std::endl;
        stream << "li "<< destReg <<", 1" << std::endl;
        stream << "j " << end << std::endl;
        stream << logical_and_false << ":" << std::endl;
        stream << "li "<< destReg <<", 0" << std::endl;
        stream << end << ":" << std::endl;


    }

    void LogicalAndExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " && ";
        rhs_->Print(stream);
        stream << ")";
    }

    void LogicalOrExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        std::string logical_or_true = context->GetNewLabel();
        std::string logical_or_false = context->GetNewLabel();
        std::string end = context->GetNewLabel();

        lhs_->EmitRISC(stream, context, "a5", type);
        stream << "bnez a5, " << logical_or_true << std::endl;
        rhs_->EmitRISC(stream, context, "a5", type);
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
