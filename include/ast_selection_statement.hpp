#include "ast_node.hpp"

namespace ast {
    class IfStatement : public Node
    {
    private:
        NodePtr condition_;
        NodePtr true_statement_;
        NodePtr false_statement_;
    public:
        IfStatement(NodePtr condition, NodePtr true_statement, NodePtr false_statement) : condition_(std::move(condition)), true_statement_(std::move(true_statement)), false_statement_(std::move(false_statement)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
        void Print(std::ostream& stream) const override;
    };
}  // namespace ast
