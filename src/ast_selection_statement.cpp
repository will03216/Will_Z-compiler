#include "ast_selection_statement.hpp"

namespace ast {
    void IfStatement::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
    {
        std::string else_label = context->GetNewLabel();
        std::string end_label = context->GetNewLabel();

        condition_->EmitRISC(stream, context);
        stream << "beqz a5, " << else_label << std::endl; // if condition is zero jump to else label

        true_statement_->EmitRISC(stream, context);
        stream << "j " << end_label << std::endl; // jump to end label after executing true statement

        stream << else_label << ":" << std::endl;
        if (false_statement_ != nullptr)
        {
            false_statement_->EmitRISC(stream, context); // execute false statement if it exists
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
