#pragma once

#include "ast_node.hpp"

namespace ast {

class DirectDeclarator : public Node
{
private:
    NodePtr identifier_;
    NodePtr parameters_;

public:
    DirectDeclarator(NodePtr identifier, NodePtr parameters = nullptr) : identifier_(std::move(identifier)), parameters_(std::move(parameters)){};

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
    void Print(std::ostream& stream) const override;
    std::string GetIdentifier() const override { return identifier_->GetIdentifier(); };
};

} // namespace ast
