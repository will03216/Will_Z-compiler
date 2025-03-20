#include "ast_selection_statement.hpp"
#include <queue>

namespace ast {
    void IfStatement::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string, TypeSpecifier type) const
    {
        std::string type_reg = "a5";

        std::string else_label = context->GetNewLabel();
        std::string end_label = context->GetNewLabel();

        condition_->EmitRISC(stream, context, "a5", TypeSpecifier::INT);
        stream << "beqz a5, " << else_label << std::endl; // if condition is zero jump to else label

        true_statement_->EmitRISC(stream, context, type_reg, type); // execute true statement
        stream << "j " << end_label << std::endl; // jump to end label after executing true statement

        stream << else_label << ":" << std::endl;
        if (false_statement_ != nullptr)
        {
            false_statement_->EmitRISC(stream, context, type_reg, type); // execute false statement if it exists
        }

        stream << end_label << ":" << std::endl;
    }

    void IfStatement::Print(std::ostream& stream) const
    {
        stream << "if (";
        condition_->Print(stream);
        stream << ") {" << std::endl;
        true_statement_->Print(stream);
        stream << "}" << std::endl;
    }


    void CaseStatement::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string, TypeSpecifier type) const
    {
        if (condition_ != nullptr)


        {
            std::string type_reg = "a4";
            std::string case_label = context->GetNewLabel();
            condition_->EmitRISC(stream, context, type_reg, type);
            stream << "bne " << type_reg << ", a5, " << case_label << std::endl;
            context->PushReg("a5", stream);
            statement_->EmitRISC(stream, context, type_reg, type);
            context->PopReg(stream);
            stream << case_label << ":" << std::endl;
        }
        else
        {
            statement_->EmitRISC(stream, context, "a4", type);

        }
    }

    void CaseStatement::Print(std::ostream& stream) const
    {
        if (condition_ != nullptr)
        {
            stream << "case ";
            condition_->Print(stream);
            stream << ": ";
        }
        statement_->Print(stream);
    }

    void SwitchStatement::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string, TypeSpecifier type) const
    {
        std::string type_reg = "a5";
        std::string end_label = context->GetNewLabel();
        context->SetExitLabel(end_label);

        condition_->EmitRISC(stream, context, type_reg, type);

        case_statements_->EmitRISC(stream, context, type_reg, type);

        stream << end_label << ":" << std::endl;

    }

    void SwitchStatement::Print(std::ostream& stream) const
    {
        stream << "switch (";
        condition_->Print(stream);
        stream << ") {" << std::endl;
        case_statements_->Print(stream);
        stream << "}" << std::endl;


    }



} // namespace ast
