#include "headers/semi_op.h"

Semi_Op::Semi_Op() {}

// BASED ON TESTING IN TERMINAL: 
// Even if (left ; right) are within parentheses, 
//   the return value of the root is the return value of the right side of the semicolon 
//   (regardless of left return value) 
bool Semi_Op::execute() {
    
    // Check for exit flag; if found, return true to exit
    if (this->prev->exit) {
        this->exit = true;
        return true;
    }

    return right->execute();
}
