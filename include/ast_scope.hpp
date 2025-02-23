#pragma once
#include <iostream>
namespace ast {
    inline void enter_scope(std::ostream& stream){
    stream << "addi	sp,sp,-32" << std::endl;
    stream << "sw	s0,28(sp)" << std::endl;
    stream << "sw	ra,24(sp)" << std::endl;
    stream << "addi	s0,sp,32" << std::endl;
    }
    inline void exit_scope(std::ostream& stream){
    stream << "lw	ra,24(sp)" << std::endl;
    stream << "lw	s0,28(sp)" << std::endl;
    stream << "addi	sp,sp,32" << std::endl;
    }
} // namespace ast
