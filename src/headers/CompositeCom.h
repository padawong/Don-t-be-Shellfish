#ifndef COMPOSITECOM_H
#define COMPOSITECOM_H

#include "Commands.h"

class CompositeCom : public Commands {
    protected:
        Commands* left;
        Commands* right;

    public:
        CompositeCom(); 
        CompositeCom(std::string command_in);
        // CompositeCom(std::string command_in, Commands* l, Commands* r) : Commands(command_in), left(l), right(r) {}
        
        Commands* parse();
        int execute();
};

#endif // COMPOSITECOM_H
