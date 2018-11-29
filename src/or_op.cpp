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
        this->success = this->right->execute();
    }
    // Based on testing in terminal:
    // If left returned true, right is not run; success of whole root is true
    else {
        this->success = true;
    }

    // If there are more operations, continue running them
    if (this->next != NULL) {

        // TEST REMOVE
        //std::cout << "within and-execute. Calling next->execute" << std::endl;

        return this->next->execute();
    }
    else {
        return this->success;
    }
}
