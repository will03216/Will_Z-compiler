# include "ast_type_specifier.hpp"

namespace ast {

    inline TypeSpecifier CalculateType(TypeSpecifier lhs, TypeSpecifier rhs) {
        if (lhs == TypeSpecifier::DOUBLE || rhs == TypeSpecifier::DOUBLE) {
            return TypeSpecifier::DOUBLE;
        }
        if (lhs == TypeSpecifier::FLOAT || rhs == TypeSpecifier::FLOAT) {
            return TypeSpecifier::FLOAT;
        }
        if (lhs == TypeSpecifier::CHAR || rhs == TypeSpecifier::CHAR) {
            return TypeSpecifier::CHAR;
        }
        return TypeSpecifier::INT;
    }

    inline int CalculatePointer(int lhs, int rhs) {
        if (lhs == 1 || rhs == 1) {
            return 1;
        }
        return 0;
    }

} // namespace ast
