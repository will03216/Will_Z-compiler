#include "ast_iteration_statement.hpp"

namespace ast {
    void WhileStatement::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string, TypeSpecifier type ) const
    {
        std::string type_reg = "a5";









        std::string loop_label = context->GetNewLabel();
        std::string condition_label = context->GetNewLabel();

        stream << "j " << condition_label << std::endl;
        stream << loop_label << ":" << std::endl;
        loop_statement_->EmitRISC(stream, context, type_reg, type);
        stream << condition_label << ":" << std::endl;
        condition_->EmitRISC(stream, context, "a5", type);
        stream << "bnez a5, " << loop_label << std::endl;


    }

    void WhileStatement::Print(std::ostream& stream) const
    {
        stream << "while (";
        condition_->Print(stream);
        stream << ") {" << std::endl;
        loop_statement_->Print(stream);
        stream << "}" << std::endl;
    }

    void DoWhileStatement::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string, TypeSpecifier type ) const
    {
        std::string type_reg = "a5";









        std::string loop_label = context->GetNewLabel();
        std::string condition_label = context->GetNewLabel();

        stream << loop_label << ":" << std::endl;
        loop_statement_->EmitRISC(stream, context, type_reg, type);
        stream << condition_label << ":" << std::endl;
        condition_->EmitRISC(stream, context, "a5", type);
        stream << "bnez a5, " << loop_label << std::endl;
    }

    void DoWhileStatement::Print(std::ostream& stream) const
    {
        stream << "do {" << std::endl;
        loop_statement_->Print(stream);
        stream << "} while (";
        condition_->Print(stream);
        stream << ");" << std::endl;
    }

    void ForStatement::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string, TypeSpecifier type ) const
    {
        std::string type_reg = "a5";









        std::string loop_label = context->GetNewLabel();
        std::string condition_label = context->GetNewLabel();
        std::string iteration_label = context->GetNewLabel();

        if (init_statement_ != nullptr)
        {
            init_statement_->EmitRISC(stream, context, "a5", TypeSpecifier::INT);
        }
        stream << "j " << condition_label << std::endl;
        stream << loop_label << ":" << std::endl;
        loop_statement_->EmitRISC(stream, context, type_reg, type);
        stream << iteration_label << ":" << std::endl;
        iteration_expression_->EmitRISC(stream, context, "a5", TypeSpecifier::INT);
        stream << condition_label << ":" << std::endl;
        condition_->EmitRISC(stream, context, "a5", TypeSpecifier::INT);
        stream << "bnez a5, " << loop_label << std::endl;
    }

    void ForStatement::Print(std::ostream& stream) const
    {
        stream << "for (";
        init_statement_->Print(stream);
        stream << "; ";
        condition_->Print(stream);
        stream << "; ";
        iteration_expression_->Print(stream);
        stream << ") {" << std::endl;
        loop_statement_->Print(stream);
        stream << "}" << std::endl;
    }

    void ForInitStatement::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string, TypeSpecifier type ) const
    {
        std::string type_reg = "a5";









        std::string loop_label = context->GetNewLabel();
        std::string condition_label = context->GetNewLabel();
        std::string iteration_label = context->GetNewLabel();

        init_statement_->EmitRISC(stream, context, "a5", TypeSpecifier::INT);
        stream << "j " << condition_label << std::endl;
        stream << loop_label << ":" << std::endl;
        loop_statement_->EmitRISC(stream, context, type_reg, type);
        stream << iteration_label << ":" << std::endl;
        iteration_expression_->EmitRISC(stream, context, "a5", TypeSpecifier::INT);
        stream << condition_label << ":" << std::endl;
        condition_->EmitRISC(stream, context, "a5", TypeSpecifier::INT);
        stream << "bnez a5, " << loop_label << std::endl;
    }

    void ForInitStatement::Print(std::ostream& stream) const
    {
        stream << "for (";
        init_statement_->Print(stream);
        stream << "; ";
        condition_->Print(stream);
        stream << "; ";
        iteration_expression_->Print(stream);
        stream << ") {" << std::endl;
        loop_statement_->Print(stream);
        stream << "}" << std::endl;
    }


} // namespace ast
