#ifndef SINGLECOM_H
#define SINGLECOM_H

#include "Commands.h"

class SingleCom : public Commands {
    public:
        SingleCom() {}
        SingleCom(std::string command_in) : Commands(command_in) {}
        
        bool parse();
        bool execute();
};

#endif // SINGLECOM_H
