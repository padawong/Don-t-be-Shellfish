#include "/headers/SingleCom.h"

SingleCom::SingleCom() {}
SingleCom::SingleCom(std::string command_in) : Commands(command_in) {}

bool SingleCom::parse() {
    return true;
}

bool SingleCom::execute() {
    return true;
}

