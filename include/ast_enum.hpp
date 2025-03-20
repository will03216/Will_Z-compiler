#include "ast_node.hpp"

namespace ast {

    class EnumDeclare : public Node
    {
    private:
        NodePtr identifier_;
        NodePtr enumerator_list_;

    public:
        EnumDeclare(NodePtr identifier, NodePtr enumerator_list) : identifier_(std::move(identifier)), enumerator_list_(std::move(enumerator_list)){};

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
        std::string GetIdentifier() const { return identifier_->GetIdentifier(); }
        TypeSpecifier GetType(std::shared_ptr<Context> context) const { return TypeSpecifier::INT; }
    };

}// namespace ast
