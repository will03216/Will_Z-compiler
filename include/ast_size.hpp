#include "ast_node.hpp"

namespace ast {

class SizeOfExpr : public Node
{
private:
    NodePtr expr_;

public:
    SizeOfExpr(NodePtr expr) : expr_(std::move(expr)) {}

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier GetType(std::shared_ptr<Context>) const override { return TypeSpecifier::INT; }
    std::string GetIdentifier() const override { return expr_->GetIdentifier(); }
};




}
