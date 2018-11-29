#include "./headers/SingleCom.h"

SingleCom::SingleCom() {}
SingleCom::SingleCom(std::vector<std::string>& cmd_v) : Commands(cmd_v) {}

bool SingleCom::execute() {
   
    bool success = true;
    
    // "exit" command must be the only string in the vector, and it must be lowercase as shown in assn2 instructions
    if (commands_vect.size() == 1 && commands_vect.at(0) == "exit") {
        exit = true;
        return true;
    }
    
    // Array of char* w/ 1 more element than vector to end w/ NULL
    char* args[commands_vect.size() + 1];

    // First element is always the command
    args [0] = (char*)commands_vect.at(0).c_str();

    // All subsequent elements are arguments
    for (int i = 1; i < commands_vect.size(); i++) {
        args[i] = (char*)commands_vect.at(i).c_str(); 
    }
    args [commands_vect.size()] = NULL;
     
    // Now we actually use syscalls: fork, waitpid, execvp
    pid_t pid = fork();

    // Child process is where we run execvp
    if (pid == 0) {
        // If the command returns an error, call perror
        if (execvp(args[0], args) == -1) {
            success = false;

            perror("Invalid command");
            
            return success;
            //return false;
        }
    }

    // Parent function waits for child to be murdered before resuming life
    if (pid > 0) {
        // since child pid = 0, we are waiting for child = 0
       if (waitpid(0, NULL, 0) == -1) {
            success = false;
            
            perror("Parent wait failed");
            //return false;
        }

    }
    return success;
    //  return true;
}

