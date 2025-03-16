#include "ast_selection_statement.hpp"

namespace ast {
    void IfStatement::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string, TypeSpecifier type) const
    {
        std::string type_reg = "a5";
        if (type == TypeSpecifier::FLOAT)
        {
            type_reg = "fa5";
        }
        else if (type == TypeSpecifier::DOUBLE)
        {
            type_reg = "fa5";
        }

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

} // namespace ast
