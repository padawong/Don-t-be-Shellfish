#ifndef SEMI_OP_H
#define SEMI_OP_H

#include "BinaryComp.h"

class Semi_Op : public BinaryComp {
    public:
        Semi_Op();
        Semi_Op(Commands* l, Commands* r);

        bool execute();
}

#endif // SEMI_OP_H
