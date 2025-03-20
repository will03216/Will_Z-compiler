#include "ast_node.hpp"

namespace ast {

    class StructDeclare : public Node
    {
    private:
        std::string identifier_;
        NodePtr struct_declaration_list_;

    public:
        StructDeclare(std::string identifier, NodePtr struct_declaration_list) : identifier_(std::move(identifier)), struct_declaration_list_(std::move(struct_declaration_list)){};

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
        std::string GetIdentifier() const { return identifier_; }
        TypeSpecifier GetType(std::shared_ptr<Context>) const { return TypeSpecifier::STRUCT; }
    };

    class StructSpecifier : public Node
    {
    private:
        std::string identifier_;

    public:
        StructSpecifier(std::string identifier) : identifier_(identifier){};

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
        std::string GetIdentifier() const { return identifier_; }
        TypeSpecifier GetType(std::shared_ptr<Context> ) const { return TypeSpecifier::STRUCT; }
    };

    class StructDeclarator : public Node
    {
    private:
        NodePtr declarator_;
        NodePtr constant_expression_;

    public:
        StructDeclarator(NodePtr declarator, NodePtr constant_expression) : declarator_(std::move(declarator)), constant_expression_(std::move(constant_expression)){};

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
        TypeSpecifier GetType(std::shared_ptr<Context> context) const { return declarator_->GetType(context); }
        std::string GetIdentifier() const { return declarator_->GetIdentifier(); }
        int IsPointer(std::shared_ptr<Context> context) const { return declarator_->IsPointer(context); }
        int IsArray() const { return declarator_->IsArray(); }
        std::variant<int, float, double> GetConst() const override {
            if (constant_expression_ != nullptr){
                return constant_expression_->GetConst();
            }
            return 0;
        }
    };

    class StructDeclaration : public Node
    {
    private:
        NodePtr specifier_qualifier_list_;
        NodePtr struct_declarator_list_;

    public:
        StructDeclaration(NodePtr specifier_qualifier_list, NodePtr struct_declarator_list) : specifier_qualifier_list_(std::move(specifier_qualifier_list)), struct_declarator_list_(std::move(struct_declarator_list)){};

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
        TypeSpecifier GetType(std::shared_ptr<Context> context) const { return specifier_qualifier_list_->GetType(context); }
        std::string GetIdentifier() const { return struct_declarator_list_->GetIdentifier(); }
        int IsPointer(std::shared_ptr<Context> context) const { return struct_declarator_list_->IsPointer(context); }
        int IsArray() const { return struct_declarator_list_->IsArray(); }
        std::variant<int, float, double> GetConst() const override {
            return struct_declarator_list_->GetConst();
        }
    };

    class StructMemberCall : public Node
    {
    private:
        NodePtr identifier_;
        std::string member_;

    public:
        StructMemberCall(NodePtr identifier, std::string member) : identifier_(std::move(identifier)), member_(member){};

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
        void EmitValueRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
        std::string GetIdentifier() const { return identifier_->GetIdentifier(); }
        TypeSpecifier GetType(std::shared_ptr<Context> context) const { return context->GetMember(context->GetScopedSymbol(identifier_->GetIdentifier())->name, member_).type; }
        //Fix this
        //int IsPointer(std::shared_ptr<Context> context) const { return context->GetStruct(identifier_->GetIdentifier())->GetMember(identifier_->GetIdentifier(), member_).type; }
    };
}
