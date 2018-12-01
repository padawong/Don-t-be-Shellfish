#include "./headers/TestCom.h"

TestCom::TestCom() : SingleCom() {}
TestCom::TestCom(std::vector<std::string>& cmd_v) : SingleCom(cmd_v) {}
            
bool TestCom::testLine() {
 
    // Default value of flag is -e
    std::string flag = "-e";
    
    // If there is a flag, set it and remove it from the vector
    if (commands_vect.at(0).at(0) == '-') {
        flag = commands_vect.at(0);
        commands_vect.erase(commands_vect.begin());
    }
        
    // If there is not just one string at this point, input is invalid. Return false
    if (commands_vect.size() != 1) {
        std::cout << "Invalid path input" << std::endl;
        return false;
    }

    // Convert vector of strings into char* array
    char* args = (char*)commands_vect.at(0).c_str();
            
    struct stat sb;
    // Need to "initialize"(?) the stat otherwise S_ISREG and S_ISDIR won't work
    stat(args, &sb);

    //CASE: Is it a vaild filepath or not?
    if (flag == "-e") {
        if (stat(args, &sb) == -1) {
            std::cout << "(False)" << std::endl;
            return false;
        }
        else {
            std::cout << "(True)" << std::endl;
            return true;
        }
    }
    
    //CASE (-f): Is it a regular file or not?            
    else if (flag == "-f") {
        if (S_ISREG(sb.st_mode)){
            std::cout<< "(True)" << std::endl;
            return true;   
        }    
        else{
           std::cout<< "(False)" << std::endl;
            return false;
        }
    }

    //CASE (-d): Is it a valid directory or not?
    else if (flag == "-d") {
        if (S_ISDIR(sb.st_mode) != 0) {
            std::cout << "(True)" << std::endl;
            return true;
        }
        else {
            std::cout << "(False)" << std::endl;
            return false;
        }
    }

    // First char in the string was '-' but doesn't match a valid flag
    else{
        std::cout << "Invalid flag" << std::endl;
        return false;
    }

}
