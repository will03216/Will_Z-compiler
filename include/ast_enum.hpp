#include "ast_node.hpp"

namespace ast {

    class EnumMember : public Node {

    private:
        std::string identifier_;
        NodePtr value_;

    public:
        EnumMember(const std::string &identifier, NodePtr value) : identifier_(identifier), value_(std::move(value)) {}
        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
        std::string GetIdentifier() const { return identifier_; }
        TypeSpecifier GetType(std::shared_ptr<Context> ) const override { return TypeSpecifier::INT; }
        int IsPointer(std::shared_ptr<Context> ) const override { return value_ ? 1 : 0; }
        std::variant<int, float, double> GetConst() const override { return value_ ? value_->GetConst() : 0; }
    };

    class EnumSpecifier : public Node {
    private:
        std::string identifier_;
        NodePtr members_;
    public:
        EnumSpecifier(const std::string &identifier, NodePtr members) : identifier_(identifier), members_(std::move(members)) {}
        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
        std::string GetIdentifier() const { return identifier_; }
        TypeSpecifier GetType(std::shared_ptr<Context> ) const override { return TypeSpecifier::INT; }
        int IsPointer(std::shared_ptr<Context> ) const override { return 0; }
    };

}// namespace ast
