#ifndef BINARYCOMP_H
#define BINARYCOMP_H

#include "CompositeCom.h"

class BinaryComp : public CompositeCom {
    protected:
        Commands* left;
        Commands* right;
    public:
        BinaryComp() {}
        BinaryComp(Commands* l, Commands* r) : CompositeCom(), left(l), right(r) {}

        //virtual bool BinaryComp::execute() = 0;
};

#endif // BINARYCOMP_H
