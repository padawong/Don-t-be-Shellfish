#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <vector>

class Commands {
    protected:
        std::string cmd;
    public:
        Commands();
        Commands(std::string command_in);// : cmd(command_in) {}
        Commands(std::vector<std::string>& string_vec_in);

        Commands* prev = NULL;
        Commands* right = NULL;

        bool success = true;
        bool exit = false;
       
        void tokenize();
        //bool parse(std::vector<std::string>& str_vec);
        virtual bool execute()= 0;


        std::vector <std::string> commands_vect;

};

#endif // COMMANDS_H
