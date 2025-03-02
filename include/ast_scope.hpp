#pragma once
#include <iostream>
namespace ast
{
    inline void enter_scope(std::ostream &stream)
    {
        stream << "addi	sp,sp,-64" << std::endl;
        stream << "sw	s0,60(sp)" << std::endl;
        stream << "sw	ra,56(sp)" << std::endl;
        stream << "addi	s0,sp,64" << std::endl;
    }

    inline void exit_scope(std::ostream &stream)
    {
        stream << "lw	ra,56(sp)" << std::endl;
        stream << "lw	s0,60(sp)" << std::endl;
        stream << "addi	sp,sp,64" << std::endl;
    }
} // namespace ast
