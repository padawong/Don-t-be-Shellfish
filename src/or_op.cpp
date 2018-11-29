#include "or_op.h"

Or_Op::Or_Op() {}

Or_Op::Or_Op(Commands* l, Commands* r) : BinaryComp(l, r) {}

bool Or_Op::execute() {

    bool left_success = left->execute();
    this->exit = left->exit;

    // Check for exit flag; if found, return true to exit
    if (this->exit) {
        return true;
    }

    // If left returned false, run right;
    //  This entire root returns whatever value right returns
    if (!left_succcess) {
        return right->execute();
    }

    // If left returned true, return true and do not run right
    else {
        return true;
    }

}
