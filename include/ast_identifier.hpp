#pragma once

#include "ast_node.hpp"

namespace ast {

class Identifier : public Node
{
private:
    std::string identifier_;

public:
    Identifier(std::string identifier) : identifier_(std::move(identifier)){};

    void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const override;
    void Print(std::ostream& stream) const override;
    std::string GetIdentifier() const override;
};

} // namespace ast
