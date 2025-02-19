#include "ast_node.hpp"

namespace ast {

void NodeList::PushBack(NodePtr item)
{
    nodes_.push_back(std::move(item));
}

void NodeList::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context) const
{
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->EmitRISC(stream, context);
    }
}

void NodeList::Print(std::ostream& stream) const
{
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->Print(stream);
    }
}
std::vector<std::string> NodeList::GetIdentifiers() const
{
    std::vector<std::string> identifiers;
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        identifiers.push_back(node->GetIdentifier());
    }
    return identifiers;
}
}
