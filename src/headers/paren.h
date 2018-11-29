#ifndef PAREN_H
#define PAREN_H

#include "CompositeCom.h"

class Paren : public CompositeCom {
    public:
        Paren();
        Paren(Commands* in);

        Commands* inner;

        bool execute();
}
#endif // PAREN_H
