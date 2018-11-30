#include "headers/Commands.h"
#include "headers/BinaryComp.h"
#include "headers/and_op.h"
#include "headers/or_op.h"
#include "headers/semi_op.h"
#include "headers/paren.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <cctype>

Commands::Commands() {}
Commands::Commands(std::string command_in) {
    cmd = command_in;
}
Commands::Commands(std::vector<std::string>& string_vec_in) {
    commands_vect = string_vec_in;
}

// Uses member vairable cmd
void Commands::tokenize() {

    // Create an array of char the size of our input command line
    char str[cmd.size()];
    strcpy(str, cmd.c_str());

    char* point;

    //std::vector<std::string> vstring;

    //Delimiter is a space
    point = strtok(str, " \n");

    //Main strtok loop 
    while(point != NULL){
        //Casting the char ptr to a string 
        std::string temp(point);

        // If comment flag is found, discontinue while loop to process commands stored in vector
        if (temp.at(0) == '#') {
            break;
        }

        commands_vect.push_back(temp);
 
        //Moving onto next command w/ strtok
        point = strtok(NULL, " ");
   }

}
/*
bool Commands::parse(std::vector<std::string>& vstring) {
    Commands* current_com;
    current_com = first_cmd;

    std::vector<std::string> vstring_chunks;
    while(vstring.size() > 0) {
        std::string temp = vstring.at(0);

        // If binary connector found, store the current vector of strings as a command
        if (temp.size() == 2 && temp.at(0) == '&' && temp.at(1) == '&') {
            
            // If vstring_chunks is not empty, then there is a vector string of commands that must be made into a command object
            // if vstring_chunks is empty, then there is (likely) a preceding command which already has a right and only assignment of and_com->prev must occur
            // This should only happen when current_com->right is null 
            if (vstring_chunks.size() > 0) {
                SingleCom* single = new SingleCom(vstring_chunks);
                current_com->right = single;
            
                vstring_chunks.clear();
            }

            And_Op* and_com = new And_Op;
            and_com->prev = current_com;
            current_com = and_com;
            // and we test and_com->prev->success for true or false
        }  
       
        else if (temp.size() == 2 && temp.at(0) == '|' && temp.at(1) == '|') {
            // Create a SingleCom instance to hold the vector of strings containing its command
            if (vstring_chunks.size() > 0) {
                SingleCom* single = new SingleCom(vstring_chunks);
                current_com->right = single;

                vstring_chunks.clear();
            }
 
            Or_Op* or_com = new Or_Op;
            or_com->prev = current_com;
            current_com = or_com;
        }
        
        else if (temp.at(temp.size() - 1) == ';') {
            // Remove the semicolon from the string
            temp.pop_back();
           
            // If there are characters before the semicolon, add them to the ongoing vector of strings 
            if (temp.size() > 0) {
                vstring_chunks.push_back(temp);
            }

            if (vstring_chunks.size() > 0) {
                SingleCom* single = new SingleCom(vstring_chunks);
                current_com->right = single;

                vstring_chunks.clear();
            }

            Semi_Op* semi_com = new Semi_Op;
            semi_com->prev = current_com;
            current_com = semi_com;
        }
       
        else if (temp.at(0) = '(') {
            // If there are strings preceding (, then it is not to be treated as a command parentheses. 
            // It is part of the string of a command 
            //   (which will return an error because the parentheses will likely not be valid)
            if (vstring_chunks.size() > 0) {
                vstring_chunks.push_back(temp);
            }

            else {
                // Remove the opening parenthese from the string
                temp.erase(0, 0);

                // Run through the strings to find the ending parentheses, then send that whole string into a recursive parse call
                // If no ending parentheses found, return false;
                for (int i = 0; i < vstring.size(); i++) {
                    // String to hold parsed characters within current string
                    std::string temp_s;

                    for (int j = 0; j < vstring.at(i).size(); j++) {
                        char current = vstring.at(i).at(j);

                        if (current == ')') {
                           // Remove the ')' from the string
                           vstring.at(i).erase(0, j);

                           // Add string thus far onto running vector
                           vstring_chunks.push_back(temp_s);

                           // Breaks the outer for loop as well
                           i = vstring.size();
                           break;
                        }                   

                        temp_s.push_back(current);
                    }
                    
                    // Add analyzed string to the running vector
                    vstring_chunks.push_back(temp_s);

                    // Remove the parsed string from the general vector
                    vstring.erase(vstring.begin());
                }
                
                // If all strings checked and no closing parentheses found, return false
                if (vstring.size() == 0) { // || !(vstring.size() == 1 && vstring.at(0).size() == 0) {
                    return false;
                }

                // Recursive call to parse the command(s) within the parentheses
                Paren* parenth = new Paren();
                Commands* temp_com = new Commands();
                // REMOVE make this assign by reference
                temp_com->commands_vect = vstring_chunks;
                temp_com->parse();
                parenth->inner = temp_com;

                // Set parentheses command to be the current one
                current_com->right = parenth;
                
                vstring_chunks.clear();
            }
        }

        else {
            vstring_chunks.push_back(temp);
        }
    }

    if (vstring_chunks.size() > 0) {
        // Add final string vector to a SingleCom
        SingleCom* single = new SingleCom(vstring_chunks);
        
        // If there are no other commands, save as first_cmd
        if (current_com->prev == NULL) {
            current_com = single;
        }
        else {
            current_com->right = single;
        }
    }
    else {
        current_com->right = NULL;
    }

    return true;
}*/
