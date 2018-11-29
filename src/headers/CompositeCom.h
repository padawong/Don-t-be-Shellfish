#ifndef COMPOSITECOM_H
#define COMPOSITECOM_H

#include "Commands.h"
#include "SingleCom.h"
#include <vector>

class CompositeCom : public Commands {
    public:
        CompositeCom(); 
        CompositeCom(std::string command_in);
        // CompositeCom(std::string command_in, Commands* l, Commands* r) : Commands(command_in), left(l), right(r) {}
        
        void parse();
        virtual bool execute() = 0;

        std::vector< std::vector<std::string> > commands_vector;
};

#endif // COMPOSITECOM_H
