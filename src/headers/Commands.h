#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

class Commands {
    protected:
        std::string cmd;
    public:
        Commands() {}
        Commands(std::string command_in) {}
        
        //bool success;
        //bool exit;
        
        virtual bool parse() = 0;
        virtual bool execute() = 0;
};

#endif // COMMANDS_H
