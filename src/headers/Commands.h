#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

class Commands {
    protected:
        std::string cmd;
    public:
        Commands() {};
        Commands(std::string command_in) {};
        
        bool success;
        bool exit;
        
        virtual Commands* parse() = 0;
        virtual int execute() = 0;
};

#endif // COMMANDS_H
