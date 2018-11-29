#include "./headers/CompositeCom.h"
#include "headers/and_op.h"
#include "headers/or_op.h"
#include "headers/semi_op.h"
#include "headers/paren.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <cctype>



CompositeCom::CompositeCom() : Commands() {}
CompositeCom::CompositeCom(std::string command_in) : Commands(command_in) {}

bool CompositeCom::parse(std::vector<std::string>& vstring) {

    // TEST REMOVE
    /*std::cout << "O WE PARSING NOW" << std::endl;
    for (int i = 0; i < commands_vect.size(); i++)
        for (int j = 0; j < commands_vect.at(i).size(); j++)
            std::cout << commands_vect.at(i).at(j);
    std::cout << std::endl;
*/

    CompositeCom* current_com = new CompositeCom;

    //TEST REMOVE
    //std::cout << "Assigned current_com to first_cmd" << std::endl;
 /*   std::cout << "vstring.size() = " << vstring.size() << std::endl;
    int test_count = 0;
*/

    std::vector<std::string> vstring_chunks;
    
    //TEST REMOVE
 //   std::cout << "vstring_chunks just made. size = " << vstring_chunks.size() << std::endl;


    while(vstring.size() > 0) {
        // TEST REMOVE
        //std::cout << "while loop number: " << test_count << std::endl;


        std::string temp = vstring.at(0);

        // If binary connector found, store the current vector of strings as a command
        if (temp.size() == 2 && temp.at(0) == '&' && temp.at(1) == '&') {
        
            // Create single command using the strings accumulated thus far
            SingleCom* single = new SingleCom(vstring_chunks);
            current_com->right = single;
            vstring_chunks.clear();

            // If this is the first command, assign the first_cmd object
            if (first_cmd == NULL) {
                this->first_cmd = current_com;
            }

            // Create an and_command object to point to the current command as prev
            // Then set it to be the current command
            And_Op* and_com = new And_Op;
            and_com->prev = current_com;

            current_com->next = and_com;
            current_com = and_com;

            // Remove the && from the vector of strings
            vstring.erase(vstring.begin());
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
 
            if (first_cmd == NULL) {
                this->first_cmd = current_com;
            }

            current_com = or_com;
 
            //TEST REMOVE
            //std::cout << "|| case reached" << std::endl;
        }
        
        else if (temp.at(temp.size() - 1) == ';') {
            // TEST REMOVE
           // std::cout << "; case reached" << std::endl;


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
 
            if (first_cmd == NULL) {
                 // TEST REMOVE
               // std::cout << "in || case, first_cmd == null" << std::endl;
                this->first_cmd = current_com;
            }
            current_com = semi_com;
        }
       
        else if (temp.at(0) == '(') {
            // TEST REMOVE
           // std::cout << "( case reached" << std::endl;



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
                CompositeCom* temp_com = new CompositeCom();
                // REMOVE make this assign by reference
                temp_com->commands_vect = vstring_chunks;
                temp_com->parse(vstring_chunks);
                parenth->inner = temp_com;

                // Set parentheses command to be the current one
                current_com->right = parenth;
                
                vstring_chunks.clear();
            }
        }

        else {

            //TEST REMOVE
            //std::cout << "else case reached" << std::endl;

            vstring_chunks.push_back(temp);
            vstring.erase(vstring.begin());

            //TEST REMOVE
            //std::cout << "vstring_chunks.at(0) = " << vstring_chunks.at(0) << std::endl;
            // TEST REMOVE
            //std::cout << "vstring_chunks.size() == " << vstring_chunks.size() << std::endl;

           
            
            
            //vstring_chunks.clear();
        }

       //TEST REMOVE
       /* test_count++;
        std::cout << "END OF WHILE LOOP REACHED." << std::endl;
        if (test_count > 15)
            break;
            */
    }
        // TEST REMOVE
        //std::cout << "vstring_chunks.size() == " << vstring_chunks.size() << std::endl;


    if (vstring_chunks.size() > 0) {
        // Add final string vector to a SingleCom
        SingleCom* single = new SingleCom(vstring_chunks);
        current_com->right = single;
                 
        //TEST REMOVE
        //std::cout << "single->commands_vect.at(0) = " << single->commands_vect.at(0) << std::endl;
        
        
        if (this->first_cmd == NULL) {
            this->first_cmd = current_com;
            this->first_cmd->next = NULL;
            
            //TEST REMOVE
/*            std::cout << "first_cmd == null but now assigned" << std::endl;
            
            std::cout << "now first_cmd->commands_vect.at(0) = " << this->first_cmd->right->commands_vect.at(0) << std::endl;
            */
        }
 
       
                
       /* 
        // If there are no other commands, save as first_cmd
        if (current_com->prev == NULL) {
            current_com = single;
        }
        else {
            current_com->right = single;
        }*/
    }

    current_com->next = NULL;

    return true;
}

bool CompositeCom::execute() {
    // TEST REMOVE
    /*std::cout << "within CompCom::execute" << std::endl;
    if (this->first_cmd == NULL) {
        std::cout << "first_cmd = null" << std::endl;
    }
    else {
        std::cout << "first_cmd != null" << std::endl;
    }*/

//    std::cout << "this->first_cmd->success = ";
//    std::cout << this->first_cmd->success << std::endl;

    std::cout << "this->first_cmd->right->commands_vect = ";
    for (int i = 0; i < this->commands_vect.size(); i++)
        for (int j = 0; j < this->commands_vect.at(i).size(); j++)
            std::cout << this->commands_vect.at(i).at(j);
    std::cout << std::endl;


    this->success = this->first_cmd->right->execute();
    // TEST REMOVE
    //std::cout << "this->success = " << this->success << std::endl;

    if (first_cmd->next == NULL) {
        return this->success;
    }
    else {
        return this->first_cmd->next->execute();
    }
}
/*
// Calls execute on each vector of string
// Responds appropriately to the connectors based on the return values of SingleCom execute
bool CompositeCom::execute() {

    bool continue_exec = true;

    // Flag detects connectors and skips the first element of the string vector if true
    bool skip_conn = false;
    
    int count;
    for (int i = 0; i < commands_vector.size(); i++) { 
        // If skip_conn flag is true, remove the first element from the string vector which is a connector
        // IDEALLY THIS LOGIC WOULD BE FIXED SO THAT THE CONNECTORS WERE THE LAST ELEMENT OF AN ARRAY MAYBE
        // THAT WAY IF FALSE, CAN JUST END, BUT THERE WOULD STILL BE SOME TRICKY, INELEGANT STUFF WITH THAT TOO
        if (skip_conn) {
            commands_vector.at(i).erase(commands_vector.at(i).begin());
            skip_conn = false;
        }


        // Constructs new single command instance, passing in the current command in the form of a vector of strings
        SingleCom* single = new SingleCom(commands_vector.at(i));

        bool exec_success = single->execute();

        // If single runs "exit", exit.
        if (single->exit) {
            this->exit = true;

            // TEST REMOVE
            //std::cout << "exit was detected. exit = " << exit << std::endl;
            return false;
        }


        // && case
        // If there are more commands and the current command returned true, proceed to next command
        // If the current command returned false and the next command begins with &&, stop executing
        if (i + 1 < commands_vector.size() && commands_vector.at(i + 1).at(0) == "&&") {
            if (!exec_success) {
                // TEST REMOVE
                //std::cout << "&& case found, !exec_success. setting false and breaking" <<  std::endl;


                continue_exec = false;


                this->success = false;
                return false;
            }
            else {
                skip_conn = true;
            }
       }

        // || case
        // If there are more commands and the current command returned false, proceed to next command
        // If the current command returned true and the next command begins with ||, stop executing
        else if (i + 1 < commands_vector.size() && commands_vector.at(i + 1).at(0) == "||") {
            if (exec_success) {
                // TEST REMOVE
                //std::cout << "|| case found, !exec_success. setting false and breaking" <<  std::endl;


                continue_exec = false;


                this->success = false;
                return false;

            }
            else {
                skip_conn = true;
            }
        }
        
        // avoid memory leaks!
        delete single;
    }

    return continue_exec;
}*/
