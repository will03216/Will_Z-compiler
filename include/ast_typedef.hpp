#include "ast_node.hpp"

namespace ast {

class TypedefDeclare : public Node
{
    private:
        NodePtr declaration_specifiers_;
        NodePtr declarator_;

    public:
        TypedefDeclare(NodePtr declaration_specifiers, NodePtr declarator): declaration_specifiers_(std::move(declaration_specifiers)), declarator_(std::move(declarator)) {}
        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
        TypeSpecifier GetType(std::shared_ptr<Context> context) const override { return declaration_specifiers_->GetType(context); }
        std::string GetIdentifier() const { return declarator_->GetIdentifier(); }
        int IsPointer(std::shared_ptr<Context> context) const { return declarator_->IsPointer(context); }
};

class TypeName : public Node
{
    private:
        std::string identifier_;

    public:
        TypeName(std::string identifier): identifier_(std::move(identifier)) {}
        void EmitRISC(std::ostream& , std::shared_ptr<Context> , std::string , TypeSpecifier ) const override {}
        void Print(std::ostream& stream) const override { stream << identifier_; }
        TypeSpecifier GetType(std::shared_ptr<Context> context) const override {
            return context->GetType(identifier_).type;
        }
        std::string GetIdentifier() const { return identifier_; }
        int IsPointer(std::shared_ptr<Context> context) const {
            return context->GetType(identifier_).is_pointer;
        }
};

} // namespace ast
