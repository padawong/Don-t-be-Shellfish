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
CompositeCom::CompositeCom(std::vector<std::string> &str_vec_in) : Commands(str_vec_in) {}

/* This still gets tricky. I ended up implementing it pretty much as a linked-list of trees (which you can technically redraw as a tree!)
 * The first command starts the chain. First_cmd and Connectors are the roots of the mini-trees that are linked together. Each has a next and prev
 *   Each checks prev->success then runs the command in its right-pointer ONLY which is the command on the right side.
 * Parentheses are a bit different. They have an inner-pointer which contains the entirety of what is between the outermost parentheses.
 *   Each inner-pointer points to another linked-list of tiny trees. These are executed and then control resumes at the next connector after the parentheses' parent 
 * Single commands and parentheses cannot exist on their own; they must be children of either first_cmd or of connectors
 * 
 * Like I said, it's tricky. I will upload a picture of the "tree" structure to GitHub
 */
bool CompositeCom::parse(std::vector<std::string>& vstring) {

    CompositeCom* current_com = new CompositeCom;
    Paren* parenth_cmd = NULL;
    
    // Vector to hold the words between operators
    // The strings are removed from the front of the full vector and added to this running vector
    std::vector<std::string> vstring_chunks;
    
    // Parse until there is nothing left to parse
    while(vstring.size() > 0) {
        // Empty string is only element; remove and proceed
        if (vstring.size() == 1 && vstring.at(0).size() == 0) {
            vstring.erase(vstring.begin());
            break;
        }

        std::string temp = vstring.at(0);

        // If binary connector found, store the current vector of strings as a command
        if (temp.size() == 2 && temp.at(0) == '&' && temp.at(1) == '&') {
       
            // If there is a parenth_cmd that has not been assigned, assign it here
            if (parenth_cmd != NULL) {
               
                vstring_chunks.clear();
               
                current_com->right = parenth_cmd;
                parenth_cmd = NULL;
            }
            
            // Otherwise create a single command to assign the vector of strings stored thus far
            else {
                SingleCom* single = new SingleCom(vstring_chunks);
                current_com->right = single;
                vstring_chunks.clear();
            }

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

            // Check if there is an unassigned parentheses command
            // If there is a parenth_cmd that has not been assigned, assign it here
            if (parenth_cmd != NULL) {
                vstring_chunks.clear();
                current_com->right = parenth_cmd;
                parenth_cmd = NULL;
            }
            else {      
                // Create single command using the strings accumulated thus far
                SingleCom* single = new SingleCom(vstring_chunks);
                current_com->right = single;
                vstring_chunks.clear();
            }

            // If this is the first command, assign the first_cmd object
            if (first_cmd == NULL) {
                this->first_cmd = current_com;
            }

            // Create an and_command object to point to the current command as prev
            // Then set it to be the current command
            Or_Op* or_com = new Or_Op;
            or_com->prev = current_com;

            current_com->next = or_com;
            current_com = or_com;

            // Remove the && from the vector of strings
            vstring.erase(vstring.begin());

        }
        
        else if (temp.at(temp.size() - 1) == ';') {
            
            // Remove the semicolon from the string
            temp.pop_back();
           
            // If there are characters before the semicolon, add them to the ongoing vector of strings 
            if (temp.size() > 0) {
                vstring_chunks.push_back(temp);
            }

            // Check if there is an unassigned parentheses command
            if (parenth_cmd != NULL) {
                vstring_chunks.clear();
                current_com->right = parenth_cmd;
                parenth_cmd = NULL;
            }
            else {
                SingleCom* single = new SingleCom(vstring_chunks);
                current_com->right = single;
                vstring_chunks.clear();
            }
            
            // If this is the first command, assign the first_cmd object
            if (first_cmd == NULL) {
                this->first_cmd = current_com;
            }

            // Create an and_command object to point to the current command as prev
            // Then set it to be the current command
            Semi_Op* semi_com = new Semi_Op;
            semi_com->prev = current_com;

            current_com->next = semi_com;
            current_com = semi_com;

            // Remove the && from the vector of strings
            vstring.erase(vstring.begin());
       }
       
        else if (temp.at(0) == '(') {

            // If there are strings preceding (, then it is not to be treated as a command parentheses. 
            // It is part of the string of a command 
            //   (which will return an error because the parentheses will likely not be valid)
            if (vstring_chunks.size() > 0) {
                vstring_chunks.push_back(temp);
            }
            
            // Run through the strings to find the ending parentheses, then send that whole string into a recursive parse call
            // If no ending parentheses found, return false;
            else {
               // Remove the opening parenthese from the string
                temp.erase(temp.begin());
                vstring.at(0).erase(vstring.at(0).begin());

                bool inside_parens = true;
                int parentheses_pair = 0;
                while (vstring.size() > 0 && inside_parens) {
                    std::string temp_s;

                    while (vstring.at(0).size() > 0) {
                        char current = vstring.at(0).at(0);

                        // If an opening parentheses is found WITHIN THE CURRENT OPEN PARENTHESES
                        //   increment count; when next closing parentheses is found, decrement count. 
                        // When count is 0, the closing parenthese found will be the corresponding one for this opening parenthese
                        if (current == '(') {
                            parentheses_pair++;
                        }

                        temp_s.push_back(current);
                        vstring.at(0).erase(vstring.at(0).begin());
                        
                        if (current == ')' && parentheses_pair == 0) {

                            // Add string thus far onto running vector
                            temp_s.erase(temp_s.size() - 1);
                            vstring_chunks.push_back(temp_s);

                            // If the character following the closing parenthese is not one of the following, the input is invalid, so end parse and return false
                            if (vstring.at(0).size() > 0) {
                                if ((vstring.at(0).at(0) != '&') && (vstring.at(0).at(0) != '|') && (vstring.at(0).at(0) != ';') && (vstring.at(0).at(0) != ')')) {
                                    return false;
                                }
                            }
                            // If this is the last element in the string, remove the string from vstring
                            else { 
                                vstring.erase(vstring.begin());
                            }
                            
                            // set to break outer while loop
                            inside_parens = false;
                            break;
                        }

                        if (current == ')' && parentheses_pair != 0) {
                            parentheses_pair--;
                        }
                    } 
                   
                    if (inside_parens == true) {
                        // Add analyzed string to the running vector
                        vstring_chunks.push_back(temp_s);

                        // Remove the parsed string from the general vector
                        vstring.erase(vstring.begin());
                    }
                }
                
                // If all strings checked and no closing parentheses found, return false
                if (inside_parens) {
                    return false;
                }

                // Recursive call to parse the command(s) within the parentheses
                CompositeCom* temp_com = new CompositeCom(vstring_chunks);
                temp_com->tokenize();
                // If parse of inner content fails, return false

                if (!temp_com->parse(temp_com->commands_vect)) {
                    return false;
                }
               
                // parenth objects are handled similarly to single commands and must therefore be stored into a variable declared at the start of parse
                Paren* parenth = new Paren;
                parenth->inner = temp_com;
                parenth_cmd = parenth;
            }
        }

        // NO MATCH WITH &&, ||, ;, (
        // Add string to running vector, remove from total vector and continue looking
        else {
            vstring_chunks.push_back(temp);
            vstring.erase(vstring.begin());
        }
    }
   
    // ALL STRINGS PARSED
    // If there are leftover strings, they will become a command 
    if (vstring_chunks.size() > 0) {
    
        // If there is a parenth_cmd that has not been assigned, assign it here
        if (parenth_cmd != NULL) {
            vstring_chunks.clear();
           
            current_com->right = parenth_cmd;
            parenth_cmd = NULL;
        }

        else {
            // Add final string vector to a SingleCom
            SingleCom* single = new SingleCom(vstring_chunks);
            current_com->right = single;
        }        
        
        if (this->first_cmd == NULL) {
            this->first_cmd = current_com;
            this->first_cmd->next = NULL;
        }
 
    }

    current_com->next = NULL;

    return true;
}

// Execute just starts the chain reaction. It's kind of messy but I just don't have the soul to fix it right now
// The idea is that if there is only one command, first_cmd will be run and nothing else happens.
// If there are more commands, then the chain reaction is set off
bool CompositeCom::execute() {
    //I would like to come back and fix this ugliness, but functionality comes first
    // It would be a purely cosmetic fix
    this->success = this->first_cmd->right->execute();
    this->first_cmd->success = this->success;
    this->exit = first_cmd->right->exit;

    if (this->exit) {
        return true;
    }

    if (first_cmd->next == NULL) {
        return this->success;
    }
    else {
        this->exit = this->first_cmd->next->exit;
        this->success = this->first_cmd->next->execute();
        return success;
    }
}
