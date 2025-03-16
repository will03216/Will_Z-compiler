# include "ast_type_specifier.hpp"

namespace ast {

    class TypeChecker
    {
    private:
        TypeSpecifier type_ = TypeSpecifier::INT;
    public:
        TypeSpecifier GetType() const { return type_; }
        void SetType(TypeSpecifier type) { type_ = type; }
    };
} // namespace ast
