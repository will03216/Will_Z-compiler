#pragma once

#include <stack>
#include <string>

namespace ast {

struct Reg {
    std::string reg;
    int offset;
};

class RegStack {
private:
    std::stack<Reg> stack_;
    int offset_ = 0;

public:

    RegStack() : offset_(0) {}

    void PushReg(std::string reg, std::ostream& stream) {
        Reg reg_struct = {reg, offset_};
        stack_.push(reg_struct);
        stream << "addi sp, sp, -4" << std::endl;
        stream << "sw " << reg << ", " << offset_ << "(sp)" << std::endl;
        offset_ -= 4;
    }

    void PopReg(std::ostream& stream) {
        if (stack_.empty()) {
            return;
        }
        stream << "lw " << stack_.top().reg << ", " << stack_.top().offset << "(sp)" << std::endl;
        stream << "addi sp, sp, 4" << std::endl;
        stack_.pop();
        offset_ += 4;
    }

    bool Empty() {
        return stack_.empty();
    }

    Reg TopReg() {
        return stack_.top();
    }

    void ExitRegStack(std::ostream& stream) {
        while (!stack_.empty()) {
            PopReg(stream);
        }
    }
};

} // namespace ast
