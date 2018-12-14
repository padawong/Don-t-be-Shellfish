#include "headers/redir.h"

Redir::Redir() {}
Redir::Redir(std::vector<std::string>& cmd_v) : SingleCom(cmd_v) {}

bool Redir::execute() {
/*    int count = 0;

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
                break;
            }

            else if (commands_vect.at(count).size() > 1) {
                perror("Invalid redirection command");
                return false;
            }
            else {
                cmd = commands_vect.at(count);
                commands_vect.erase(commands_vect.begin() + count);
                break;
            }
        }
        count++;
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
        if (pipe(fd) < 0) {
            perror("Pipe failed");
            return false;
        }
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
                    perror("Invalid command within pipe");
                    return false;
                }
*/                /*if (waitpid(0, NULL, 0) == -1) {
                    perror("Parent wait failed");
                    return false;
                }*/
/*            }
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
*//* 
        if (cmd == "|") {
            //write(
            dup2(fd[1], 1);
            close(fd[0]);
        }*/
/*   }

    return true;
*/


    // Referring heavily to https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
   

    int count = 0;

    // save current in and out
    int temp_in= dup(0);
    int temp_out = dup(1);
    bool fdin_cmd = false;
    bool fdout_cmd = false;
    std::string in_file;
    std::string out_file;
    int fd_in, fd_out;
    std::string op;

    int vect_index = 0;
<<<<<<< HEAD

    std::vector<std::string> temp_commands;

    std::vector<std::vector<std::string> > all_commands;

    while (commands_vect.size() > 0) {
        if (commands_vect.at(0) == "<" || commands_vect.at(0) == ">" || commands_vect.at(0) == ">>" || commands_vect.at(0) == "|") {


            if (commands_vect.at(0) == "<") {
                fdin_cmd = true;
                commands_vect.erase(commands_vect.begin());

                in_file = commands_vect.at(0);
            }
            if (commands_vect.at(0) == ">" || commands_vect.at(0) == ">>") {
                fdout_cmd = true;
                op = commands_vect.at(0);
                commands_vect.erase(commands_vect.begin());

                out_file = commands_vect.at(0);
            }

            // Command fully stored into vector; move to next slot in vector
            //vect_index++;
            all_commands.push_back(temp_commands);

            commands_vect.erase(commands_vect.begin());
        }
        
        else {
            temp_commands.push_back(commands_vect.at(0));
            //all_commands.at(vect_index).push_back(commands_vect.at(0));
            commands_vect.erase(commands_vect.begin());
        }
    }

    if (fdin_cmd) {
        char* file[1];
        file[0] = (char*)in_file.c_str();
        if ((fd_in = open(file[0], O_RDONLY, 0)) < 0) {
            perror("Could not open input file");
            return false;
        }
        //dup2(fd_in, STDIN_FILENO);
        //close(fd_in);
    }
    else {
        fd_in = dup(temp_in);
    }



    for (vect_index = 0; vect_index < all_commands.size(); vect_index++) {
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);

        // Last command
        if (vect_index == all_commands.size() - 1) {
            char* file[1];
            file[0] = (char*)out_file.c_str();
            // Output redirection
            if (fdout_cmd) {
                // Overwrite
                if (op == ">") {
                    fd_out = open(file[0], O_CREAT|O_TRUNC|O_WRONLY, 0644);
                }

                // Append
                if (op == ">>") {
                    fd_out = open(file[0], O_WRONLY|O_APPEND);
                }

                if (fd_out < 0) {
                    perror("Could not open output file");
                    return false;
                }
                            }
            else {
                fd_out = dup(temp_out);
            }
        }

        // Not last command
        else {
            // create pipe
            // Setup for piping
            int fd[2];
            if (pipe(fd) < 0) {
                perror("Pipe failed");
                return false;
            }

            fd_in = fd[0];
            fd_out = fd[1];
            
        } 
=======

    std::vector<std::string> temp_commands;

    std::vector<std::vector<std::string> > all_commands;

    while (commands_vect.size() > 0) {
        if (commands_vect.at(0) == "<" || commands_vect.at(0) == ">" || commands_vect.at(0) == ">>" || commands_vect.at(0) == "|") {


            if (commands_vect.at(0) == "<") {
                fdin_cmd = true;
                commands_vect.erase(commands_vect.begin());

                in_file = commands_vect.at(0);
            }
            if (commands_vect.at(0) == ">" || commands_vect.at(0) == ">>") {
                fdout_cmd = true;
                op = commands_vect.at(0);
                commands_vect.erase(commands_vect.begin());

                out_file = commands_vect.at(0);
            }

            // Command fully stored into vector; move to next slot in vector
            //vect_index++;
            all_commands.push_back(temp_commands);

            commands_vect.erase(commands_vect.begin());
        }
        
        else {
            temp_commands.push_back(commands_vect.at(0));
            //all_commands.at(vect_index).push_back(commands_vect.at(0));
            commands_vect.erase(commands_vect.begin());
        }
    }

    if (fdin_cmd) {
        char* file[1];
        file[0] = (char*)in_file.c_str();
        if ((fd_in = open(file[0], O_RDONLY, 0)) < 0) {
            perror("Could not open input file");
            return false;
        }
        //dup2(fd_in, STDIN_FILENO);
        //close(fd_in);
    }
    else {
        fd_in = dup(temp_in);
    }



    for (vect_index = 0; vect_index < all_commands.size(); vect_index++) {
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);

        // Last command
        if (vect_index == all_commands.size() - 1) {
            char* file[1];
            file[0] = (char*)out_file.c_str();
            // Output redirection
            if (fdout_cmd) {
                // Overwrite
                if (op == ">") {
                    fd_out = open(file[0], O_CREAT|O_TRUNC|O_WRONLY, 0644);
                }

                // Append
                if (op == ">>") {
                    fd_out = open(file[0], O_WRONLY|O_APPEND);
                }

                if (fd_out < 0) {
                    perror("Could not open output file");
                    return false;
                }
                            }
            else {
                fd_out = dup(temp_out);
            }
        }

        // Not last command
        else {
            // create pipe
            // Setup for piping
            int fd[2];
            if (pipe(fd) < 0) {
                perror("Pipe failed");
                return false;
            }

            fd_in = fd[0];
            fd_out = fd[1];
        } 

        // Redirect output
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);

        // TEST REMOVE
        //std::cout << "about to convert command to char*" << std::endl;
        
        // Convert command to char* arrays
        char* command[all_commands.at(vect_index).size() + 1];
        for (int i = 0; i < all_commands.at(vect_index).size(); i++) {
            command[i] = (char*)all_commands.at(vect_index).at(i).c_str();
        }
        command[all_commands.at(vect_index).size()] = NULL;

        // TEST REMOVE
        //std::cout << "Finished converting command to char*" << std::endl;
/*
        vect_index++;

        char* right_cmd[all_commands.at(vect_index).size() + 1];
        for (int i = 0; i < all_commands.at(vect_index).size(); i++) {
            right_txt[i] = (char*)all_commands.at(vect_index).at(i).c_str();
        }
        right_txt[right_in.size()] = NULL;
        */
        // TEST REMOVE
/*        for (int i = 0; i < command_in.size(); i++) {
           // std::cout << "command_in[" << i << "] = " << command_in.at(i) << std::endl;
            std::cout << "command[" << i << "] = " << command[i] << std::endl;
        }
        for (int i = 0; i < right_in.size(); i++) {
           // std::cout << "right_in[" << i << "] = " << right_in.at(i) << std::endl;
            std::cout << "right_txt[" << i << "] = " << right_txt[i] << std::endl;
        }
*/


        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return false;
        }

        // Run current command batch
        if (pid == 0) {
            if (execvp(command[0], command) < 0) {
            perror("Invalid command");
                return false;
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

        count++;
    }

    // Restore default in/out
    dup2(temp_in, 0);
    dup2(temp_out, 1);
    close(temp_in);
    close(temp_out);
>>>>>>> 63e6beb2f856197c2ef56c38ae24370471aed332

        // Redirect output
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);

<<<<<<< HEAD
        // TEST REMOVE
        //std::cout << "about to convert command to char*" << std::endl;
        
        // Convert command to char* arrays
        char* command[all_commands.at(vect_index).size() + 1];
        for (int i = 0; i < all_commands.at(vect_index).size(); i++) {
            command[i] = (char*)all_commands.at(vect_index).at(i).c_str();
        }
        command[all_commands.at(vect_index).size()] = NULL;

        // TEST REMOVE
        //std::cout << "Finished converting command to char*" << std::endl;
/*
        vect_index++;

        char* right_cmd[all_commands.at(vect_index).size() + 1];
        for (int i = 0; i < all_commands.at(vect_index).size(); i++) {
            right_txt[i] = (char*)all_commands.at(vect_index).at(i).c_str();
        }
        right_txt[right_in.size()] = NULL;
        */
        // TEST REMOVE
/*        for (int i = 0; i < command_in.size(); i++) {
           // std::cout << "command_in[" << i << "] = " << command_in.at(i) << std::endl;
            std::cout << "command[" << i << "] = " << command[i] << std::endl;
        }
        for (int i = 0; i < right_in.size(); i++) {
           // std::cout << "right_in[" << i << "] = " << right_in.at(i) << std::endl;
            std::cout << "right_txt[" << i << "] = " << right_txt[i] << std::endl;
        }
*/


        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return false;
        }

        // Run current command batch
        if (pid == 0) {
            if (execvp(command[0], command) < 0) {
            perror("Invalid command");
                return false;
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

        count++;
    }

    // Restore default in/out
    dup2(temp_in, 0);
    dup2(temp_out, 1);
    close(temp_in);
    close(temp_out);


=======
>>>>>>> 63e6beb2f856197c2ef56c38ae24370471aed332
    return true;
}

/*

// Splits the raw input into a new format:
// All operators have commands on left side, pipes have commands on right side, and redirection has files on right side
// left-side commands are saved as individual strings in the vector
// However, when a redirection operator is encountered, it is prepended to the filename, e.g. "<file.txt"
// execute() will search for the operator and open the file appropriately
bool Redir::parse() {
    std::vector<std::string> parsed_input;
    
    // Leftmost string is always a command
    parsed_input_push_back(commands_vect.at(0));
    commands_vect.erase(commands_vect.begin());

    
    while (commands_vect.size() > 1) {
        if (commands_vect.at(0) == ">" || commands_vect.at(0) == "<" || commands_vect.at(0) == ">>") {
            // Push the operator into the start of the current parsed_input string
            // Using a for loop to make it easier to deal with ">>"
            for (int i = 0; i < commands_vect.at(0).size(); i++) {
                parsed_input.at(parsed_input.size()).push_back(commands_vect.at(0).at(i));
            }
            commands_vect.erase(commands_vect.begin());
        }

        // Stores commands and/or filenames
        for (int i = 0; i < commands_vect.at(0).size(); i++) {

            // If redirection string encountered, break to restart while loop
            if (commands_vect.at(0) == ">" || commands_vect.at(0) == "<" || commands_vect.at(0) == ">>") {
                break;
            }

            // If there's a |, just ignore it
            if (commands_vect.at(0) == "|") {
                commands_vect.erase(commands_vect.begin());
            }

            parsed_input.at(parsed_input.size()).push_back(commands_vect.at(0).at(i));

            if (commands_vect.at(0).size() == 0) {
                commands_vect.erase(commands_vect.begin());
            }
        }
    }

    // Only happens when the last operator was pipe
    // Save the last command to the vector (this will not be a filename)
    if (commands_vect.size() == 0) {
        parsed_input.push_back(commands_vect.at(0));
    }
    */
