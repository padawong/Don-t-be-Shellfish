#include "headers/paren.h"

Paren::Paren() : CompositeCom () {}
Paren::Paren(CompositeCom* in) : CompositeCom () , inner(in){}

bool Paren::execute() {

    // TEST REMOVE
    std::cout << "within paren execute" << std::endl;

    return inner->first_cmd->right->execute();
}
