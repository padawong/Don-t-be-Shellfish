#ifndef COMPOSITECOM_H
#define COMPOSITECOM_H

#include "Commands.h"
#include "SingleCom.h"
#include <vector>

class CompositeCom : public Commands {
    public:
        CompositeCom(); 
        CompositeCom(std::string string_in);
        CompositeCom(std::vector<std::string> &str_vec_in);

        bool parse(std::vector<std::string> &commands_in);
        bool execute();


        CompositeCom* next = NULL;

        CompositeCom* first_cmd = NULL;
        //std::vector< std::vector<std::string> > commands_vector;
};

#endif // COMPOSITECOM_H
