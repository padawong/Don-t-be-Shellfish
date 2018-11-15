#ifndef COMPOSITECOM_H
#define COMPOSITECOM_H

#include "Commands.h"

class CompositeCom : public Commands {
    protected:
        Command* left;
        Command* right;

    public:
        CompositeCom() {};
        CompositeCom(std::string command_in) : Commands(command_in) {};
        // I think we need a constructor that takes in the left and right commands
        
        Commands* parse();
        int execute();
};

#endif // COMPOSITECOM_H
