#ifndef SINGLECOM_H
#define SINGLECOM_H

#include "Commands.h"
#include <string>
#include <vector>

class SingleCom : public Commands {
    public:
        SingleCom();
        SingleCom(std::vector <std::string> cmd_v);
        
        //bool parse();
        bool execute();

        std::vector <std::string> commands_vect;
        bool exit = false;
};

#endif // SINGLECOM_H
