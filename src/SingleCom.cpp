#include "./headers/SingleCom.h"
#include "./headers/TestCom.h"
#include "headers/Redir.h"

SingleCom::SingleCom() {}
SingleCom::SingleCom(std::vector<std::string> &cmd_v) : Commands(cmd_v) {}

bool SingleCom::execute() {
   
    // CHECK FOR EXIT
    // "exit" command must be the only string in the vector, and it must be lowercase as shown in assn2 instructions
    if (commands_vect.size() == 1 && commands_vect.at(0) == "exit") {
        exit = true;
        return true;
    }


    // CHECK IF TEST PROMPT
    if(commands_vect.at(0).at(0) == '[' || commands_vect.at(0) == "test"){
        // Check for closing bracket. If does not exist, return false
        // If does exist, remove from vector
        if (commands_vect.at(0).at(0) == '[') {

            // Super ugly, but basically it's: the last character of the last string in the vector
            if (commands_vect.at(commands_vect.size() - 1).at(commands_vect.at(commands_vect.size() - 1).size() - 1) == ']') {
                // Remove opening bracket
                commands_vect.at(0).erase(commands_vect.at(0).begin());

                // If the opening bracket was the only element in the string, remove the string
                if (commands_vect.at(0).size() == 0) {
                    commands_vect.erase(commands_vect.begin());
                }
                // Remove closing bracket
                commands_vect.at(commands_vect.size() - 1).erase(commands_vect.at(commands_vect.size() - 1).size() - 1);
            }
            else {
                std::cout << "Test prompt missing closing brace" << std::endl;
                return false;
            }
        }

        // Otherwise just remove "test"
        else {
            //delete the first element of the array so we only pass through the flag and filepath
            commands_vect.erase(commands_vect.begin());
        }
        TestCom* testComm = new TestCom(this->commands_vect);
        
        this->success = testComm->testLine();

        // TEST REMOVE
        //std::cout << "this->success = " << this->success << std::endl;

        return success;
    }

    // CHECK IF REDIRECTION OR PIPING
    // If so, outsource the execution
    // MIGHT IMPLEMENT THIS LATER, BUT IT'S NOT REALLY NECESSARY:
    // If within a quotation marks, disregard the operator
    // int in_quote = 0;

    // vector containing <, >, >> possibly contains a preceding number; checks for this case too
    for (int i = 0; i < commands_vect.size(); i++) {
        // If necessary to include handling for situations specifying file descriptor 0, 1, 2, will come back and re-add it. For now, just wanna get the basics working
        if (commands_vect.at(i).at(0) == '>' || commands_vect.at(i).at(0) == '<' || commands_vect.at(i).at(0) == '|') {// || (commands_vect.at(i).size() > 1 && (commands_vect.at(i).at(1) == '>' || commands_vect.at(i).at(1) == '<'))) {
            Redir* redir_cmd = new Redir(this->commands_vect);
            this->success = redir_cmd->execute();
            return success;
        }
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
        if (execvp(args[0], args) < 0) {
            success = false;

            perror("Invalid command");
            
            //return success;
            return false;
        }
    }

    // Parent function waits for child to be murdered before resuming life
    if (pid > 0) {
        // since child pid = 0, we are waiting for child = 0
       if (waitpid(0, NULL, 0) == -1) {
            success = false;
            
            perror("Parent wait failed");
            //return false;
            return false;
        }

    }

    return success;
    //  return true;
}

