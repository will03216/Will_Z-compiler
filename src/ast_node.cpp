#include "ast_node.hpp"

namespace ast {

void NodeList::PushBack(NodePtr item)
{
    nodes_.push_back(std::move(item));
}

void NodeList::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
{
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->EmitRISC(stream, context, destReg, type);
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

void NodeList::EmitValueRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
{
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->EmitValueRISC(stream, context, destReg);
    }
}

std::vector<TypeSpecifier> NodeList::GetTypes(std::shared_ptr<Context> context) const
{
    std::vector<TypeSpecifier> types;
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        types.push_back(node->GetType(context));
    }
    return types;
}

std::vector<Symbol> NodeList::GetSymbols(std::shared_ptr<Context> context) const
{
    std::vector<Symbol> symbols;
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        Symbol node_symbol = {node->GetIdentifier(), node->GetType(context), 0, node->IsArray(), node->IsPointer(context)};
        symbols.push_back(node_symbol);
    }
    return symbols;
}

} // namespace ast
