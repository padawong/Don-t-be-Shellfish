#include "./headers/SingleCom.h"

SingleCom::SingleCom() {}
SingleCom::SingleCom(std::vector < std::string > cmd_v) : Commands(), commands_vect(cmd_v) {}

/*
bool SingleCom::parse() {
    return true;
}
*/

bool SingleCom::execute() {
    for (int i = 0; i < commands_vect.size(); i++) {
 
        // "exit" command is quite strict; must be the only string in the vector, and it must be lowercase as shown in assn2 instructions
        if (commands_vect.size() == 1 && commands_vect.at(0) == "exit") {
            exit = true;
            return true;
        }
        std::string current = commands_vect.at(i);
        
       return true; 
    }
}

