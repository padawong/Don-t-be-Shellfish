#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

class Commands {
    protected:
        std::string cmd;
    public:
        Commands() {}
        Commands(std::string command_in) : cmd(command_in) {}
        
        bool success = true;
        bool exit = false;
        
        //virtual bool parse() = 0;
        virtual bool execute(/*Commands* cmdptr*/) = 0;

        Commands* first_cmd;
};

#endif // COMMANDS_H
