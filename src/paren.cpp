#include "headers/paren.h"

Paren::Paren() : CompositeCom () {}
Paren::Paren(Commands* in) : CompositeCom () , inner(in){}

bool Paren::execute() {
    return inner->execute();
}
