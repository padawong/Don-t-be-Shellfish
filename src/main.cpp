#include <iostream> 
#include <string>
#include "./headers/CompositeCom.h"
#include <unistd.h> //NEW
#include <limits.h> //NEW


int main () {
  
    bool exit_loop = true;
    std::string cmd; 

    // ALTERNATE REALITY BLACKMAGIC CODE DEMO
    // TEST REMOVE
    // int count = 0;

    // Start a main command loop    
    do{
        // ALTERNATE REALITY BLACKMAGIC CODE DEMO
        // TEST REMOVE
        //std::cout << "Start of do loop. count = " << count << std::endl;

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

        //TEST REMOVE
        //std::cout << "newCommand not yet tokenized, but created" << std::endl;


        newCommand->tokenize();

        // TEST REMOVE
        //std::cout << "tokenize complete" << std::endl;

        newCommand->parse(newCommand->commands_vect);
 
        // TEST REMOVE
        //std::cout << "parse complete" << std::endl;

        newCommand->execute();
        exit_loop = newCommand->exit;
        
        /*
        // ALTERNATE REALITY BLACKMAGIC CODE DEMO
        // TEST REMOVE
        std::cout << "back in main. exit_loop = " << exit_loop << std::endl;
        std::cout << "count = " << count << std::endl;
       
        // ALTERNATE REALITY BLACKMAGIC CODE DEMO
        // TEST REMOVE
        ++count;
        */
        
        delete newCommand;
    } while(exit_loop == false);
    // ALTERNATE REALITY BLACKMAGIC CODE DEMO
    // && std::cout << "CHECKING WHILE"<< std::endl);  // Determine when to exit 

  
    return 0;
}
