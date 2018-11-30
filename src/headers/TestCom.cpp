ifndef TESTCOM_H
#define TESTCOM_H

#include "Commands.h"
#include <string>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <sys/stat.h>



class TestCom : public Commands {
  
    public:
        vector <string> cmds;

    private:
        TestCom::TestCom(){}
        TestCom::TestCom(std::vector<std::string>& cmd_v) : Commands(cmd_v) {}
            
        
        bool testLine(){
    
            struct stat sb;

            string flag = argv[1];

           
            // Array of char* w/ 1 more element than vector to end w/ NULL
                  char* args[commands_vect.size() + 1];
            
                     // First element is always the command
                          args [0] = (char*)commands_vect.at(0).c_str();
            
                              // All subsequent elements are arguments
                                  for (int i = 1; i < commands_vect.size(); i++) {
                                          args[i] = (char*)commands_vect.at(i).c_str(); 
                                             }


            if( flag == "-f"){
                if (S_ISREG(sb.st_mode) != 0){
                    std::cout<< "(True)" << std::endl;
                }    
                else{
                    std::cout<< "(False)" << std:: endl;
                }
            }


            else if(flag == "-d"){
                if(S_ISDIR(sb.st_mode) != 0){
                    std::cout<< "(True)" << std::endl;
                }
                else{
                    std::cout<< "(False)" << std::endl;
                }
            }


            else{
                if (stat(argv[1], &sb)){
                    std::cout<< "(True)" << std::endl;
                }
                else{
                    std::cout<< "(False)" << std::endl;
                }
            }

      


#endif TESTCOM_H


















