#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <variant>

#include "ast_context.hpp"
#include "ast_scope.hpp"
#include "ast_type_specifier.hpp"
#include "ast_symbol_table.hpp"
#include "ast_type_checker.hpp"

namespace ast {

class Node
{
public:
    virtual ~Node() {}
    virtual void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const = 0;
    virtual void Print(std::ostream& stream) const = 0;
    virtual std::string GetIdentifier() const { return ""; };
    virtual std::vector<std::string> GetIdentifiers() const { return {}; };
    virtual int IsArray() const { return -1; };
    virtual std::unique_ptr<const Node> GetValue() const { return nullptr; };
    virtual void EmitValueRISC(std::ostream& , std::shared_ptr<Context> , std::string ) const {};
    virtual TypeSpecifier GetType(std::shared_ptr<Context> ) const { return TypeSpecifier::VOID; };
    virtual std::vector<TypeSpecifier> GetTypes(std::shared_ptr<Context> ) const { return {}; };
    virtual int IsPointer(std::shared_ptr<Context> ) const { return 0; };
    virtual std::vector<Symbol> GetSymbols(std::shared_ptr<Context> ) const { return {}; };
    virtual std::vector<std::unique_ptr<const Node>> GetValues() const { return {}; };
    virtual std::variant<int, float, double> GetConst() const { return 0; };
    virtual std::vector<std::variant<int, float, double>> GetConstList() const { return {}; };


};

// If you don't feel comfortable using std::unique_ptr, you can switch NodePtr to be defined
// as a raw pointer instead here and your project should still compile, although you'll need
// to add destructors to avoid leaking memory
// (and get rid of the now unnecessary std::move-s)
using NodePtr = std::unique_ptr<const Node>;

class NodeList : public Node
{
private:
    std::vector<NodePtr> nodes_;

public:
    NodeList() = default;
    NodeList(NodePtr first_node) { nodes_.push_back(std::move(first_node)); }

    virtual void PushBack(NodePtr item);
    virtual void EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const override;
    virtual void Print(std::ostream& stream) const override;
    virtual std::vector<std::string> GetIdentifiers() const override;
    virtual void EmitValueRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const override;
    virtual std::vector<TypeSpecifier> GetTypes(std::shared_ptr<Context> context) const override;
    virtual std::vector<Symbol> GetSymbols(std::shared_ptr<Context> context) const override;
    virtual TypeSpecifier GetType(std::shared_ptr<Context> context) const override;
    virtual std::vector<std::variant<int, float, double>> GetConstList() const override;
};

} // namespace ast
