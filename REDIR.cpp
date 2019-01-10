bool Redir::execute() {

    // Referring heavily to https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
   

    int count = 0;
    
    while (commands_vect.size() > 0) {
         // save current in and out
        int temp_in= dup(0);
        int temp_out = dup(1);
        int fd_in, fd_out;

        std::vector<std::string> command_in;
        std::string op;
        std::vector<std::string> filename_in;
        bool store_command = true;
        // Command and filename stored; another op encountered so stop reading input and execute the pending
        bool execution_pending = false;

        // Compile complete command; when second operator encountered, break and process the info
        while (commands_vect.size() > 0) {
            if (commands_vect.at(0) == "<" || commands_vect.at(0) == ">" || commands_vect.at(0) == ">>" || commands_vect.at(0) == "|") {
                if (execution_pending) {
                    break;
                }
                op = commands_vect.at(0);
                commands_vect.erase(commands_vect.begin());
                //break;
                store_command = false;
            }
            
            if (store_command) {
                command.push_back(commands_vect.at(0));
            }
            else {
                filename.push_back(commands_vect.at(0));
            }
            commands_vect.erase(commands_vect.begin());
        }

        // Convert command & filename to char* arrays
        char* command[command_in.size() + 1];
        for (int i = 0; i < command_in.size(); i++) {
            command[i] = (char*)command_in.at(i).c_str();
        }
        char* filename[filename_in.size() + 1];
        for (int i = 0; i < filename_in.size(); i++) {
            filename[i] = (char*)filename_in.at(i).c_str();
        }

        // Setup for piping
        int fd[2];
        if (op == "|") {
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

        // Run current command batch
        if (pid == 0) {
            // Heavily referencing https://stackoverflow.com/questions/11515399/implementing-shell-in-c-and-need-help-handling-input-output-redirection
            // Input redirection
            if (op == "<") {
                int fd0;
                if ((fd0 = open(filename[0], O_RDONLY, 0)) < 0) {
                    perror("Could not open input file");
                    return false;
                }
                dup2(fd0, STDIN_FILENO);
                close(fd0);
            }
/*            else {
                fd_in = dup(temp_in);
            }*/

            //Output redirection
            if (op == ">" || op == ">>") {
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
/*            else {
                fd_out = dup(temp_out);
            }*/

            // USING https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/pipe.html
            // Not sure if it's necessary to have two forks, but this website does, so I'm gonna try that
            // Otherwise I don't see a good way to run execvp on both commands
            if (op == "|") {
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
                    /*if (waitpid(0, NULL, 0) == -1) {
                        perror("Parent wait failed");
                        return false;
                    }*/
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








        count++;
    }

    return true;
}
