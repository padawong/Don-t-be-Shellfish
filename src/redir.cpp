#include "headers/redir.h"

Redir::Redir() {}
Redir::Redir(std::vector<std::string>& cmd_v) : SingleCom(cmd_v) {}

bool Redir::execute() {
    std::string left_str, cmd, right_str;

    for (int i = 0; i < commands_vect.size(); i++) {
        // If an operator is encountered, stop adding to left_str and break
        if (commands_vect.at(i) == '<' || commands_vect.at(i) == '>' || commands_vect.at(i) == '|') {
            // If '>' found, check if it is the ">>" command rather than ">" command
            if (commands_vect.at(i) == '>' && i+1 < commands_vect.size() && commands_vect.at(i+1) == '>') {

                cmd = ">>";
            }
            else {
                cmd.push_back(commands_vect.at(i));
            }
            break;
        }
        left_str.push_back(commands_vect.at(i);
    }





}
