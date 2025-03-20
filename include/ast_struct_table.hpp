#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <variant>

namespace ast {

    struct StructMember {
        std::string identifier;
        TypeSpecifier type;
        std::variant<int, float, double> constant;
        int offset;
    };

    struct Struct {
        std::string identifier;
        std::vector<StructMember> members;
        int size;
    };

    class StructTable {
    private:
        std::unordered_map<std::string, Struct> struct_table_;

    public:

        void AddStruct(const std::string& identifier, const Struct& s)
        {
            struct_table_[identifier] = s;
        }

        const Struct* GetStruct(const std::string& identifier) const
        {
            if (!HasStruct(identifier))
            {
                throw std::runtime_error("StructTable: Struct not found" + identifier);
            }
            return &struct_table_.at(identifier);
        }

        bool HasStruct(const std::string& identifier) const
        {
            return struct_table_.find(identifier) != struct_table_.end();
        }

        StructMember GetMember(const std::string& struct_identifier, const std::string& member_identifier) const
        {
            const Struct* s = GetStruct(struct_identifier);
            for (const auto& member : s->members)
            {
                if (member.identifier == member_identifier)
                {
                    return member;
                }
            }
            throw std::runtime_error("StructTable: Member not found");
        }

    };

}
