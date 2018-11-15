#ifndef COMPOSITECOM_H
#define COMPOSITECOM_H

#include "Commands.h"

class CompositeCom : public Commands {
    protected:
        Command* left;
        Command* right;

    public:
        CompositeCom() {}
        CompositeCom(std::string command_in, Command* l, Command, r) : Commands(command_in), left(l), right(r) {}
        
        Commands* parse();
        int execute();
};

#endif // COMPOSITECOM_H
