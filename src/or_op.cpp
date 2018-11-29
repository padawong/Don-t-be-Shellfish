#include "headers/or_op.h"

Or_Op::Or_Op() {}

bool Or_Op::execute() {

    // Check for exit flag; if found, return true to exit
    if (this->prev->exit) {
        this->exit = true;
        return true;
    }

    // If previous operation returned false, run right;
    //  This entire root returns whatever value right returns
    if (!this->prev->success) {
        return right->execute();
    }

    // Based on testing in terminal:
    // If left returned true, return true and do not run right
    else {
        return true;
    }

}
