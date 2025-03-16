#include "ast_node.hpp"

namespace ast {
    class WhileStatement : public Node
    {
    private:
        NodePtr condition_;
        NodePtr loop_statement_;
    public:
        WhileStatement(NodePtr condition, NodePtr loop_statement) : condition_(std::move(condition)), loop_statement_(std::move(loop_statement)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
    };

    class DoWhileStatement : public Node
    {
    private:
        NodePtr condition_;
        NodePtr loop_statement_;

    public:
        DoWhileStatement(NodePtr condition, NodePtr loop_statement) : condition_(std::move(condition)), loop_statement_(std::move(loop_statement)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
    };

    class ForStatement : public Node
    {
    private:
        NodePtr init_statement_;
        NodePtr condition_;
        NodePtr iteration_expression_;
        NodePtr loop_statement_;

    public:
        ForStatement(NodePtr init_statement, NodePtr condition, NodePtr iteration_expression, NodePtr loop_statement) : init_statement_(std::move(init_statement)), condition_(std::move(condition)), iteration_expression_(std::move(iteration_expression)), loop_statement_(std::move(loop_statement)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
    };

    class ForInitStatement : public Node
    {
    private:
        NodePtr init_statement_;
        NodePtr condition_;
        NodePtr iteration_expression_;
        NodePtr loop_statement_;
    public:
        ForInitStatement(NodePtr init_statement, NodePtr condition, NodePtr iteration_expression, NodePtr loop_statement) : init_statement_(std::move(init_statement)), condition_(std::move(condition)), iteration_expression_(std::move(iteration_expression)), loop_statement_(std::move(loop_statement)) {}

        void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
        void Print(std::ostream& stream) const override;
    };


}  // namespace ast
