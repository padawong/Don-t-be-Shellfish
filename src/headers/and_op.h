#ifndef AND_OP_H
#define AND_OP_H

#include "BinaryComp.h"

class And_Op : public BinaryComp {
    public:
        And_Op();
        //And_Op(Commands* l, Commands* r);

        bool execute();
};

#endif // AND_OP_H
