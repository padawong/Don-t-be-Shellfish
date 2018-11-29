#include "semi_op.h"

Semi_Op::Semi_Op() {}

Semi_Op::Semi_Op(Commands* l, Commands* r) : BinaryComp(l, r) {}

// BASED ON TESTING IN TERMINAL: 
// Even if (left ; right) are within parentheses, 
//   the return value of the root is the return value of the right side of the semicolon 
//   (regardless of left return value) 
bool Semi_Op::execute() {
    left->execute();
    this->exit = left->exit;

    // Check for exit flag; if found, return true to exit
    if (this->exit) {
        return true;
    }

    return right->execute();
}
