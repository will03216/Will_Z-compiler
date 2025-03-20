#pragma once

#include <string_view>
#include <stdexcept>

namespace ast {

enum class TypeSpecifier
{
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    VOID,
    SIGNED,
    UNSIGNED,
    STRUCT,
    ENUM
};

template<typename LogStream>
LogStream& operator<<(LogStream& ls, const TypeSpecifier& type)
{
    const auto TypeToString = [&type] {
        switch (type)
        {
        case TypeSpecifier::INT:
            return "int";
        case TypeSpecifier::FLOAT:
            return "float";
        case TypeSpecifier::DOUBLE:
            return "double";
        case TypeSpecifier::CHAR:
            return "char";
        case TypeSpecifier::SIGNED:
            return "signed";
        case TypeSpecifier::UNSIGNED:
            return "unsigned";
        case TypeSpecifier::VOID:
            return "void";
        case TypeSpecifier::STRUCT:
            return "struct";
        case TypeSpecifier::ENUM:
            return "enum";
        }
        throw std::runtime_error("Unexpected type specifier");
    };
    return ls << TypeToString();
}
} // namespace ast
