#ifndef OR_OP_H 
#define OR_OP_H

#include "BinaryComp.h"

class Or_Op : public BinaryComp {
    public:
        Or_Op();
        //Or_Op(Commands* l, Commands* r);

        bool execute();
};

#endif // OR_OP_H
