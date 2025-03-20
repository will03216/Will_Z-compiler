#pragma once

#include <string>
#include <unordered_map>

namespace ast {

    struct TypeStruct {
        std::string name;
        TypeSpecifier type;
        int size;
        int is_pointer;
    };

    class TypeTable {
        private:
            std::unordered_map<std::string, TypeStruct> table;

        public:
            TypeTable() {
                table["int"] = {"int", TypeSpecifier::INT, 4, 0};
                table["float"] = {"float", TypeSpecifier::FLOAT, 4, 0};
                table["double"] = {"double", TypeSpecifier::DOUBLE, 8, 0};
                table["char"] = {"char", TypeSpecifier::CHAR, 1, 0};
                table["void"] = {"void", TypeSpecifier::VOID, 0, 0};
            }

            void AddType(std::string name, TypeSpecifier type, int size, int is_pointer) {
                table[name] = {name, type, size, is_pointer};
            }

            TypeStruct GetType(std::string name) {
                if (table.find(name) == table.end()) {
                    throw std::runtime_error("Type not found");
                }
                return table[name];
            }

            bool HasType(std::string name) {
                return table.find(name) != table.end();
            }
    };
}
