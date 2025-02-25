#include "ast_identifier.hpp"

namespace ast {

    void Identifier::EmitRISC(std::ostream& stream, std::shared_ptr<Context>, std::string) const
{
    stream << identifier_;
}

void Identifier::Print(std::ostream& stream) const
{
    stream << identifier_;
};

std::string Identifier::GetIdentifier() const
{
    return identifier_;
}
}
