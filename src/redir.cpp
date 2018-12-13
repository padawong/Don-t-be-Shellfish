#include "headers/redir.h"

Redir::Redir() {}
Redir::Redir(std::vector<std::string>& cmd_v) : SingleCom(cmd_v) {}

bool Redir::execute() {
    std::string cmd;
    char* left_txt[1000];
    int count = 0;

    // Build the left_str while looking for the redirection or pipe operator
    while (commands_vect.size() > 0) {
        // If an operator is encountered, stop adding to left_str and break
        // Support for file_descriptor+redir_op not yet implemented (like when it's 2>)
        if (commands_vect.at(count).at(0) == '<' || commands_vect.at(count).at(0) == '>' || commands_vect.at(count).at(0) == '|') {
            // If '>' found, check if it is the ">>" command rather than ">" command
            if (commands_vect.at(count).at(0) == '>' && commands_vect.at(count).size() > 1 && commands_vect.at(count).at(1) == '>') {
                // If the string starting with > is neither ">" nor ">>"
                if (commands_vect.at(count).size() > 2) {
                    perror("Invalid redirection command");
                    return false;
                }
                
                cmd = ">>";
                commands_vect.erase(commands_vect.begin() + count);
                //commands_vect.at(count) = NULL;
                break;
            }

            // REMOVE: This will need to be updated when support for more verbose redirection commands is implemented (e.g. 2>&1)
            else if (commands_vect.at(count).size() > 1) {
                perror("Invalid redirection command");
                return false;
            }
            else {
                cmd = commands_vect.at(count);
                commands_vect.erase(commands_vect.begin() + count);
                //commands_vect.at(count) = NULL;
                break;
            }
        }

        //left_txt[count] = (char*)commands_vect.at(0).c_str(); 
        count++;
        //commands_vect.erase(commands_vect.begin());
    }
    char* right_txt[commands_vect.size() - count];
    // REMOVE: might want to add handling for nothing following the cmd operator
    
    for (int i = 0; count < commands_vect.size(); i++) {
        right_txt[i] = (char*)commands_vect.at(count).c_str();
        count++;
    }
    
    // Decrements count so that the filename is not saved into args
    // (this fixed the input is output problem!!)
    count--;

    // Hacky, but if it's an echo, erase the last string which is the filepath
    if (commands_vect.at(0) == "echo") {
        commands_vect.pop_back();
    }

    char* args[count + 1];
    for (int i = 0; i < count; i++) {
        args[i] = (char*)commands_vect.at(i).c_str();
    }
    args [count] = NULL;

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return false;
    }

    if (pid == 0) {
        //Assuming valid input, at this point we have our left_str, cmd, right_str

        // Heavily referencing https://stackoverflow.com/questions/11515399/implementing-shell-in-c-and-need-help-handling-input-output-redirection
        // Input redirection
        if (cmd == "<") {
            int fd0;
            if ((fd0 = open(right_txt[0], O_RDONLY, 0)) < 0) {
                perror("Could not open input file");
                return false;
            }
            dup2(fd0, STDIN_FILENO);
            close(fd0);
        }

        if (cmd == ">" || cmd == ">>") {
            int fd1;
            if (cmd == ">") {
                fd1 = open(right_txt[0], O_CREAT|O_TRUNC|O_WRONLY, 0644);
            }
            if (cmd == ">>") {
                fd1 = open(right_txt[0], O_WRONLY|O_APPEND);
            }
            if (fd1 < 0) {
                perror("Could not open output file");
                return false;
            }
            dup2(fd1, STDOUT_FILENO);
            close(fd1);
        }

        if (cmd == "|") {
            //write(
        }

        if (execvp(args[0], args) < 0) {
            perror("Invalid command");
            return false;
        }

        
    }
    
    if (pid > 0) {
    // since child pid = 0, we are waiting for child = 0
       if (waitpid(0, NULL, 0) == -1) {
            success = false;
            
            perror("Parent wait failed");
            return false;
        }
    }

    return true;




}
