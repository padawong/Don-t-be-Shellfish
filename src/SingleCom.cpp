#include "./headers/SingleCom.h"

SingleCom::SingleCom() {}
SingleCom(std::vector<std::string> cmd_v) : Commands(), commands_vect(cmd_v) {}

/*
bool SingleCom::parse() {
    return true;
}
*/

bool SingleCom::execute() {
    return true;
}

