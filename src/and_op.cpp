#include "and_op.h"

And_Op::And_Op() {}

And_Op::And_Op(Commands* l, Commands* r) : BinaryComp(l, r) {}

bool And_Op::execute() {

    bool left_success = left->execute();
    this->exit = left->exit;

    // Check for exit flag; if found, return true to exit
    if (this->exit) {
        return true;
    }

    // If left returned true, run right;
    //  This entire root returns whatever value right returns 
    if (left_succcess) {
        return right->execute();
    }

    // If left returned false, return false and do not run right
    else {
        return false;
    }
}
