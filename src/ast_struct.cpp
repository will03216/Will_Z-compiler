#include "ast_struct.hpp"
#include "ast_struct_table.hpp"

namespace ast {

void StructDeclare::EmitRISC(std::ostream& , std::shared_ptr<Context> context, std::string , TypeSpecifier ) const
{
    std::vector<Symbol> symbols = struct_declaration_list_->GetSymbols(context);
    std::vector<StructMember> members;
    std::vector<std::variant<int, float, double>> constants = struct_declaration_list_->GetConstList();
    int count = 0;
    int size = 0;
    for (const auto& symbol : symbols)
    {
        int offset = size;
        if (symbol.type == TypeSpecifier::INT)
        {
            size += 4;
        }
        else if (symbol.type == TypeSpecifier::FLOAT)
        {
            size += 4;
        }
        else if (symbol.type == TypeSpecifier::DOUBLE)
        {
            size += 8;
        }
        else if (symbol.type == TypeSpecifier::CHAR)
        {
            size += 1;
        }
        else
        {
            throw std::runtime_error("StructDeclare: TypeSpecifier not supported");
        }
        members.push_back({symbol.name, symbol.type, constants[count], offset});
        count++;
    }

    Struct s = {identifier_, members, size};
    context->AddStruct(identifier_, s);
}

void StructDeclare::Print(std::ostream& stream) const
{
    stream << "StructDeclare(";
    stream << identifier_;
    stream << ", ";
    struct_declaration_list_->Print(stream);
    stream << ")";
}

void StructSpecifier::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
{
    (void)stream;
    (void)context;
    (void)destReg;
    (void)type;
}

void StructSpecifier::Print(std::ostream& stream) const
{
    stream << "StructSpecifier(";
    stream << identifier_;
    stream << ")";
}

void StructDeclarator::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
{
    (void)stream;
    (void)context;
    (void)destReg;
    (void)type;
}

void StructDeclarator::Print(std::ostream& stream) const
{
    stream << "StructDeclarator(";
    declarator_->Print(stream);
    stream << ", ";
    if (constant_expression_ != nullptr)
    {
        constant_expression_->Print(stream);
    }
    stream << ")";
}

void StructDeclaration::Print(std::ostream& stream) const
{
    stream << "StructDeclaration(";
    specifier_qualifier_list_->Print(stream);
    stream << ", ";
    struct_declarator_list_->Print(stream);
    stream << ")";
}

void StructDeclaration::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
{
    (void)stream;
    (void)context;
    (void)destReg;
    (void)type;
}

void StructMemberCall::Print(std::ostream& stream) const
{
    stream << "StructMemberCall(";
    identifier_->Print(stream);
    stream << ", ";
    stream << member_;
    stream << ")";
}

void StructMemberCall::EmitRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg, TypeSpecifier type) const
{
    identifier_->EmitRISC(stream, context, destReg, type);
    StructMember member = context->GetMember(context->GetScopedSymbol(identifier_->GetIdentifier())->name, member_);
    if (member.type == TypeSpecifier::INT)
    {
        stream << "lw " << destReg << ", " << member.offset << "(" << destReg << ")" << std::endl;
    }
    else if (member.type == TypeSpecifier::FLOAT)
    {
        stream << "flw f" << destReg << ", " << member.offset << "(" << destReg << ")" << std::endl;
    }
    else if (member.type == TypeSpecifier::DOUBLE)
    {
        stream << "fld f" << destReg << ", " << member.offset << "(" << destReg << ")" << std::endl;
    }
    else if (member.type == TypeSpecifier::CHAR)
    {
        stream << "lb " << destReg << ", " << member.offset << "(" << destReg << ")" << std::endl;
    }
    else
    {
        throw std::runtime_error("StructMemberCall: TypeSpecifier not supported");
    }

}

void StructMemberCall::EmitValueRISC(std::ostream& stream, std::shared_ptr<Context> context, std::string destReg) const
{
    identifier_->EmitRISC(stream, context, destReg, TypeSpecifier::STRUCT);
    StructMember member = context->GetMember(context->GetScopedSymbol(identifier_->GetIdentifier())->name, member_);
    stream << "add " << destReg << ", " << destReg << ", " << member.offset << std::endl;
}

}
