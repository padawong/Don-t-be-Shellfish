include "./headers/TestCom.h"

        TestCom::TestCom(){}
        TestCom::TestCom(std::vector<std::string>& cmd_v) :SingleCom(cmd_v) {}
            
        
        bool testLine(){//RETURN A STRING OR A BOOL????
          
            // Array of char* w/ 1 more element than vector to end w/ NULL
            char* args[commands_vect.size()];
            
            // First element is always the command
            args [0] = (char*)commands_vect.at(0).c_str();
            
            // All subsequent elements are arguments
            for (int i = 1; i < commands_vect.size(); i++) {
                args[i] = (char*)commands_vect.at(i).c_str(); 
            }



            struct stat sb;
            string flag = argv[1];
  
            //CASE (-f): Is it a regular file or not?            
            if( flag == "-f"){
               if (S_ISREG(sb.st_mode) != 0){
                    std::cout<< "(True)" << std::endl;
                    
               }    
                else{
                   std::cout<< "(False)" << std::endl;
                }
            }

            //CASE (-d): Is it a valid directory or not?
            else if (flag == "-d"){
                if(S_ISDIR(sb.st_mode) != 0){
                    std::cout << "(True)" << std::endl;
                }
                else{
                    std::cout << "(False)" << std::endl;
                }
            }

            //CASE: Is it a vaild filepath or not?
            else{
                if(stat(argv[1], &sb)){
                    std::cout << "(True)" << std::endl;
                }
                else{
                    std::cout << "(False)" << std::endl;
                }
            }

        }



