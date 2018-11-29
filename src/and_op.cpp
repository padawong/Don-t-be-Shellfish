#include "headers/and_op.h"

And_Op::And_Op() {}

bool And_Op::execute() {

    // Check for exit flag; if found, return true to exit
    if (this->prev->exit) {
        this->exit = true;
        return true;
    }

    // If previous operation returned true, run right;
    //  This entire root returns whatever value right returns 
    if (this->prev->success) {
        return right->execute();
    }

    // If previous operation returned false, the entire ampersand root returns false even though right operation is not run
    else {
        return false;
    }
}
