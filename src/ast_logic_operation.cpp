#include "ast_logic_operation.hpp"

namespace ast {
    void LessThanExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
    {
        lhs_->EmitRISC(stream, context);
        stream << "mv a4,a5"<< std::endl;
        rhs_->EmitRISC(stream, context);
        stream << "slt a5,a4,a5" << std::endl;
    }
    void LessThanExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " < ";
        rhs_->Print(stream);
        stream << ")";
    }

    void GreaterThanExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
    {
        lhs_->EmitRISC(stream, context);
        stream << "mv a4,a5"<< std::endl;
        rhs_->EmitRISC(stream, context);
        stream << "sgt a5,a4,a5" << std::endl;
    }
    void GreaterThanExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " > ";
        rhs_->Print(stream);
        stream << ")";
    }

    void LessThanEqualExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
    {
        lhs_->EmitRISC(stream, context);
        stream << "mv a4,a5"<< std::endl;
        rhs_->EmitRISC(stream, context);
        stream << "sgt a5,a4,a5" << std::endl;
        stream << "xori a5,a5,1" << std::endl;
    }
    void LessThanEqualExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " <= ";
        rhs_->Print(stream);
        stream << ")";
    }

    void GreaterThanEqualExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
    {
        lhs_->EmitRISC(stream, context);
        stream << "mv a4,a5"<< std::endl;
        rhs_->EmitRISC(stream, context);
        stream << "slt a5,a4,a5" << std::endl;
        stream << "xori a5,a5,1" << std::endl;
    }
    void GreaterThanEqualExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " >= ";
        rhs_->Print(stream);
        stream << ")";
    }

    void EqualityExpr::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
    {
        lhs_->EmitRISC(stream, context);
        stream << "mv a4,a5"<< std::endl;
        rhs_->EmitRISC(stream, context);
        stream << "sub a5,a4,a5" << std::endl;
        stream << "seqz a5,a5" << std::endl;
    }

    void EqualityExpr::Print(std::ostream& stream) const
    {
        stream << "(";
        lhs_->Print(stream);
        stream << " == ";
        rhs_->Print(stream);
        stream << ")";
    }
}
