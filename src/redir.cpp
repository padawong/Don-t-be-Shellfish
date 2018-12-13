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
    // Store the left side of the operator into args
    // REMOVE: this won't work if operators with no left side are supported
    if (commands_vect.at(count - 1) == "echo") {
        commands_vect.erase(commands_vect.begin() + (--count));
    }
    char* args[count + 1];
    // TEST REMOVE
      //std::cout << "    final count = " << count << std::endl;
      //std::cout << "    commands_vect.size() - count + 1 = " << commands_vect.size() - count + 1 << std::endl;
    for (int i = 0; i < count; i++) {
        args[i] = (char*)commands_vect.at(i).c_str();

        // TEST REMOVE
        //std::cout << "args[" << i << "] = " << commands_vect.at(i) << std::endl;
    }
    args[count] = NULL;

    char* right_txt[commands_vect.size() - (count + 1)];
    // REMOVE: might want to add handling for nothing following the cmd operator
    
    // Store the string on the right side of the operator
    int right_size = 0;
    for (int i = 0; count < commands_vect.size(); i++) {
        right_txt[i] = (char*)commands_vect.at(count).c_str();


        // TEST REMOVE
        //std::cout << "right_txt[" << i << "] = " << commands_vect.at(count) << std::endl;
        //std::cout << "    count = " << count << std::endl;

        count++;
        right_size++;
    }
    right_txt[right_size] = NULL;
    // TEST REMOVE
    //std::cout << "count = " << count << std::endl;
    
    int fd[2];
    if (cmd == "|") {
        pipe(fd);
    }
    
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

        // Output redirection
        if (cmd == ">" || cmd == ">>") {
            int fd1;

            // Overwrite
            if (cmd == ">") {
                fd1 = open(right_txt[0], O_CREAT|O_TRUNC|O_WRONLY, 0644);
            }

            // Append
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

        // USING https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/pipe.html
        // Not sure if it's necessary to have two forks, but this website does, so I'm gonna try that
        // Otherwise I don't see a good way to run execvp on both commands
        if (cmd == "|") {
            pid_t pipe_pid = fork();

            if (pipe_pid < 0) {
                perror("Fork failed");
                return false;
            }
            if (pipe_pid == 0) {            
                dup2(fd[0], 0);
                // "child does not need this end of hte pipe"
                close(fd[1]);
                if (execvp(right_txt[0], right_txt) < 0) {
                    perror("Pipe right command invalid");
                    return false;
                }
            }
            if (pipe_pid > 0) {
                dup2(fd[1], 1);
                close(fd[0]);
                if (execvp(args[0], args) < 0) {
                    perror("Invalid command");
                    return false;
                }
                if (waitpid(0, NULL, 0) == -1) {
                    perror("Parent wait failed");
                    return false;
                }
            }
        }

        else {
            if  (execvp(args[0], args) < 0) {
                perror("Invalid command");
                return false;
            }
        }

        
    }
    
    if (pid > 0) {
    // since child pid = 0, we are waiting for child = 0
       if (waitpid(0, NULL, 0) == -1) {
            //success = false;
            
            perror("Parent wait failed");
            return false;
        }
/* 
        if (cmd == "|") {
            //write(
            dup2(fd[1], 1);
            close(fd[0]);
        }*/
   }

    return true;




}
