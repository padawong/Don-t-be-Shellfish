#include <iostream> 
#include <string>
#include "./headers/CompositeCom.h"
#include <unistd.h> //NEW
#include <limits.h> //NEW


int main () {
    // need to implement 3 componenets
    // 1) Initialize shell with $
    // 2) Interpret and execute commands
    // 3) How/when to terminate
   
    bool exit_loop = true;
    std::string cmd; 


    // Start a main command loop    
    do{
        
        //store host name and username 
        char hostname[HOST_NAME_MAX];
        char username[LOGIN_NAME_MAX];
                            
        gethostname(hostname , HOST_NAME_MAX);
        getlogin_r(username, LOGIN_NAME_MAX);
                                               
        std::cout << username;
        std::cout << "@";
        std::cout << hostname;
        //print money
        std::cout << "$ ";
        
        //read user input
        std::string cmd; 
        std::getline(std::cin, cmd);

        //Pass to Commands constructor
        CompositeCom* newCommand = new CompositeCom(cmd); 
        newCommand->parse();
        newCommand->execute();
        exit_loop = newCommand->exit;
        
    } while(!exit_loop);  // Determine when to exit 

  
    return 0;
}
