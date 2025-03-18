
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

public:
    void PushReg(std::string reg, int offset) {
        Reg r = {reg, offset};
        stack_.push(r);
    }

    Reg PopReg() {
        Reg r = stack_.top();
        stack_.pop();
        return r;
    }

    bool Empty() {
        return stack_.empty();
    }

    Reg TopReg() {
        return stack_.top();
    }
};

} // namespace ast
