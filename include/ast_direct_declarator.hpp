#pragma once

#include "ast_node.hpp"

namespace ast {

class DirectDeclarator : public Node
{
private:
    NodePtr identifier_;
    NodePtr parameters_;
    int is_array_ ;

public:
DirectDeclarator(NodePtr identifier, NodePtr parameters = nullptr, int is_array = -1) : identifier_(std::move(identifier)), parameters_(std::move(parameters)), is_array_(is_array) {};

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
    void Print(std::ostream& stream) const override;
    std::string GetIdentifier() const override { return identifier_->GetIdentifier(); };
    int IsArray() const override { return is_array_; };
};

} // namespace ast
