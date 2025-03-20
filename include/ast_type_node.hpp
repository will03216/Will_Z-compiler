#include "ast_node.hpp"

namespace ast {

    class TypeSpecifierNode : public Node
    {
    private:
        TypeSpecifier type_;

    public:
        TypeSpecifierNode(TypeSpecifier type) : type_(type) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override {(void)stream; (void)context; (void)destReg; (void)type;}
        void Print(std::ostream& stream) const override { stream << type_; }
        TypeSpecifier GetType(std::shared_ptr<Context>) const override { return type_; }
    };

}// namespace ast
