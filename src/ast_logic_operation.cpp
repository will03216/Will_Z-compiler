#include "ast_logic_operation.hpp"

namespace ast {
    void LessThanExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg,  TypeSpecifier type) const
    {
        if (type == TypeSpecifier::INT)
        {
            lhs_->EmitRISC(stream, context, "a4", type);
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "slt "<< destReg <<",a4,a5" << std::endl;
        }
        else if (type == TypeSpecifier::FLOAT)
        {
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
            stream << "flt.s "<< destReg <<",fa4,fa5" << std::endl;
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
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

    void GreaterThanExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if (type == TypeSpecifier::INT)
        {
            lhs_->EmitRISC(stream, context, "a4", type);
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "sgt "<< destReg <<",a4,a5" << std::endl;
        }
        else if (type == TypeSpecifier::FLOAT)
        {
            lhs_->EmitRISC(stream, context, "fa5", type);
            rhs_->EmitRISC(stream, context, "fa4", type);
            stream << "flt.s "<< destReg <<",fa4,fa5" << std::endl;
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            lhs_->EmitRISC(stream, context, "fa5", type);
            rhs_->EmitRISC(stream, context, "fa4", type);
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

    void LessThanEqualExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if (type == TypeSpecifier::INT)
        {
            lhs_->EmitRISC(stream, context, "a4", type);
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "sgt "<< destReg <<",a4,a5" << std::endl;
            stream << "xori "<< destReg <<","<< destReg <<",1" << std::endl;
        }
        else if (type == TypeSpecifier::FLOAT)
        {
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
            stream << "fle.s "<< destReg <<",fa4,fa5" << std::endl;
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
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

    void GreaterThanEqualExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if (type == TypeSpecifier::INT){
            lhs_->EmitRISC(stream, context, "a4", type);
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "slt "<< destReg <<",a4,a5" << std::endl;
            stream << "xori "<< destReg <<","<< destReg <<",1" << std::endl;
        }
        else if (type == TypeSpecifier::FLOAT)
        {
            lhs_->EmitRISC(stream, context, "fa5", type);
            rhs_->EmitRISC(stream, context, "fa4", type);
            stream << "fle.s "<< destReg <<",fa4,fa5" << std::endl;
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            lhs_->EmitRISC(stream, context, "fa5", type);
            rhs_->EmitRISC(stream, context, "fa4", type);
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

    void EqualityExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if(type == TypeSpecifier::INT) {
            lhs_->EmitRISC(stream, context, "a4", type);
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "sub "<< destReg <<",a4,a5" << std::endl;
            stream << "seqz "<< destReg <<","<< destReg << std::endl;
        }
        else if(type == TypeSpecifier::FLOAT) {
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
            stream << "feq.s "<< destReg <<",fa4,fa5" << std::endl;
        }
        else if(type == TypeSpecifier::DOUBLE) {
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
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

    void InequalityExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
    {
        if(type == TypeSpecifier::INT){
            lhs_->EmitRISC(stream, context, "a4", type);
            rhs_->EmitRISC(stream, context, "a5", type);
            stream << "sub "<< destReg <<",a4,a5" << std::endl;
            stream << "snez "<< destReg <<","<< destReg << std::endl;
        }
        else if(type == TypeSpecifier::FLOAT){
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
            stream << "fne.s "<< destReg <<",fa4,fa5" << std::endl;
        }
        else if(type == TypeSpecifier::DOUBLE){
            lhs_->EmitRISC(stream, context, "fa4", type);
            rhs_->EmitRISC(stream, context, "fa5", type);
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
