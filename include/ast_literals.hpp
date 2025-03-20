#pragma once
#include <string>
#include <unordered_map>
#include <ostream>
#include <iomanip>

class LiteralTable
{
private:
    int nextLabel = 1;
    std::unordered_map<std::string, int> stringMap;
public:
    LiteralTable() : nextLabel(0) {}

    int AddString(std::string value)
    {
        if (stringMap.find(value) == stringMap.end())
        {
            stringMap[value] = nextLabel++;
        }
        return stringMap[value];
    }

    int GetStringLabel(std::string value)
    {
        if (stringMap.find(value) == stringMap.end())
        {
            return -1;
        }
        return stringMap[value];
    }

    void ConstructLiterals(std::ostream& stream)
    {
        if (stringMap.empty())
        {
            return;
        }
        stream << ".section .rodata" << std::endl;
        for (auto const& [key, val] : stringMap)
        {
            stream << "str_" << val << ": .asciz \"" << EscapeString(key) << "\"" << std::endl;
        }
    }

private:
    std::string EscapeString(const std::string& str) const
    {
        std::ostringstream escaped;
        for (char c : str)
        {
            switch (c)
            {
                case '\n': escaped << "\\n"; break;
                case '\t': escaped << "\\t"; break;
                case '\r': escaped << "\\r"; break;
                case '\\': escaped << "\\\\"; break;
                case '\"': escaped << "\\\""; break;
                default: escaped << c; break;
            }
        }
        return escaped.str();
    }
};
