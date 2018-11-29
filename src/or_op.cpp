#include "or_op.h"

Or_Op::Or_Op() {}

Or_Op::Or_Op(Commands* l, Commands* r) : BinaryComp(l, r) {}

bool Or_Op::execute() {

}
