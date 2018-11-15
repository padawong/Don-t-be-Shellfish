#include "./headers/CompositeCom.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <cctype>

CompositeCom::CompositeCom() {}
CompositeCom::CompositeCom(std::string command_in) : Commands(command_in) {}

/* This gets tricky.
 * We make a vector of string vectors. Each string vector contains one full command.
 * As we use strtok to generate these vectors, it is checking for connectors or the comment flag.
 * If the connectors are found, we pushback the vector string onto the vector of vectors.
 * If the comment flag is found, we break from the strtok process and proceed to executing the commands now in the vector of vectors.
 */
bool CompositeCom::parse() {

    // Create an array of char the size of our input command line
    char str[cmd.size()];
    char* point;

    //vector to hold all our commands 
    std::vector< std::vector<std::string> > vector_vector;
    std::vector<std::string> vstring;

    //Delimiter is a space
    point = strtok(str, " ");

    // Add the first token to the first vector
    std::string s(point);
    vstring.push_back(s);

    //Main strtok loop 
    while(point != NULL){
    
        //Casting the char ptr to a string 
        std::string temp(point);

        // If comment flag is found, discontinue while loop to process commands stored in vector
        if (temp.at(0) == '#') {
            break;
        }

        // If connector found, append to vector of strings, then append that vector to the vector of vectors
        if (temp.at(0) == '&' || temp.at(0) == '|' || temp.at(temp.size() - 1) == ';') {
            // The last element in the current vector will be the connector 
               // OR POSSIBLY A WORD FOLLOWED BY A SEMICOLON
            vstring.push_back(temp);
            vector_vector.push_back(vstring);
        }
        else {
            vstring.push_back(temp);
        }

        //Appending string to vector
        //vstring.push_back(temp);    

        //Moving onto next command w/ strtok     
        point = strtok(NULL, " ");
    }


/*    int counter = 0;
    bool cmdSuccess = true;
    while(counter < vstring.size() && cmdSuccess ){
        
         
        Commands* newCommand = new SingleCom()
        
        cmdSuccess = newCommand->parse();        
        counter++;
    }
*/
}

bool CompositeCom::execute(/*Commands* cmdptr*/) {
    return true;
}
