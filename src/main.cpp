#include <iostream> 
#include <string>
#include "./headers/CompositeCom.h"



int main () {
    // need to implement 3 componenets
    // 1) Initialize shell with $
    // 2) Interpret and execute commands
    // 3) How/when to terminate
   
    bool isExit = false;
    std::string cmd; 


    // Start a main command loop    
    do{
        //print money
        std::cout << "$ ";
        
        //read user input
        std::string cmd; 
        std::getline(std::cin, cmd);

        //Pass to Commands constructor
        Commands* newCommand = new CompositeCom(cmd);    
        bool isExit = newCommand->parse(); // parse() will only return false if "exit" command detected

    }while(!isExit);  // Determine when to exit 

  
    return 0;
}
