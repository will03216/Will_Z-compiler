# include "ast_type_specifier.hpp"

namespace ast {

    class TypeChecker
    {
    private:
        TypeSpecifier type_ = TypeSpecifier::VOID;
    public:
        TypeSpecifier GetType() const { return type_; }
        void SetType(TypeSpecifier type) { type_ = type; }
    };
} // namespace ast
