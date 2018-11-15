#ifndef COMPOSITECOM_H
#define COMPOSITECOM_H

#include "Commands.h"

class CompositeCom : public Commands {
    public:
        CompositeCom() {};
        CompositeCom(std::string command_in) : Commands(command_in) {};
        
        Commands* parse();
        int execute();
};

#endif // COMPOSITECOM_H
