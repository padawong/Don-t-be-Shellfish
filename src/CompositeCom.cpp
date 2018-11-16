#include "./headers/CompositeCom.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <cctype>

CompositeCom::CompositeCom() {}
CompositeCom::CompositeCom(std::string command_in) : Commands(command_in) {}

/* This gets tricky.
 * We use a vector of string vectors. Each string vector contains one full command.
 * As we use strtok to generate these vectors, it is checking for connectors or the comment flag.
 * If the connectors are found, we pushback the vector string onto the vector of vectors.
 * If the comment flag is found, we break from the strtok process and proceed to executing the commands now in the vector of vectors.
 */
void CompositeCom::parse() {

    // Create an array of char the size of our input command line
    char str[cmd.size()];
    strcpy(str, cmd.c_str());

    char* point;

    std::vector<std::string> vstring;

    //Delimiter is a space
    point = strtok(str, " \n");

    // Add the first token to the first vector
    //std::string s(point);
    //vstring.push_back(s);

    //Main strtok loop 
    while(point != NULL){

        // TEST REMOVE
        //std::cout << "WITHIN WHILE LOOP" << std::endl;

        //Casting the char ptr to a string 
        std::string temp(point);

        // If comment flag is found, discontinue while loop to process commands stored in vector
        if (temp.at(0) == '#') {
            break;


            // TEST REMOVE
            //std::cout << "IN # CASE" << std::endl;
        }

        // If connector found, append to vector of strings, then append that vector to the vector of vectors
        if (temp.at(0) == '&' || temp.at(0) == '|') {
            commands_vector.push_back(vstring);

            // TEST REMOVE
            //std::cout << "FOUND & OR |. TEMP IS: " << temp << std::endl;

            // The FIRST element in the NEXT vector will be the connector 
            vstring.clear();
            vstring.push_back(temp);

            // TEST REMOVE
            //std::cout << "IN &| CASE" << std::endl;
        }

        // If a string ends with a semicolon, append the word to the current vector, but begin the next vector
        // ; is not saved at all because its presence is unnecessary
        else if (temp.at(temp.size() - 1) == ';') {
            // Remove the semicolon from the string
            temp.pop_back();

            vstring.push_back(temp);
            commands_vector.push_back(vstring);

            vstring.clear();

        // TEST REMOVE
        //std::cout << "IN ; CASE" << std::endl;

        }

        else {
            vstring.push_back(temp);


            // TEST REMOVE
            //std::cout << "IN ELSE CASE" << std::endl;

        }

        //Appending string to vector
        //vstring.push_back(temp);

        //Moving onto next command w/ strtok
        point = strtok(NULL, " ");
    }

    // Add final string vector to vector vector
    commands_vector.push_back(vstring);

    // TEST REMOV               break;E
    //std::cout << "HELLO" << std::endl;
    //std::cout << commands_vector.size() << std::endl;

    // TEST REMOVE
    /*for (int i = 0; i < commands_vector.size(); i++) {
        for (int j = 0; j < commands_vector.at(i).size(); j++) {
            std::cout << commands_vector.at(i).at(j);
        }
    } std::cout << "\n\n" << std::endl;*/
}

// Calls execute on each vector of string
// Responds appropriately to the connectors based on the return values of SingleCom execute
bool CompositeCom::execute(/*Commands* cmdptr*/) {

    bool continue_exec = true;

    // Flag detects connectors and skips the first element of the string vector if true
    bool skip_conn = false;
    
    int count;
    for (int i = 0; i < commands_vector.size(); i++) {

        // TEST REMOVE
        //std::cout << "BEGINNING OF WHILE LOOP. continue_exec = " << continue_exec << std::endl;

        // If skip_conn flag is true, remove the first element from the string vector which is a connector
        // IDEALLY THIS LOGIC WOULD BE FIXED SO THAT THE CONNECTORS WERE THE LAST ELEMENT OF AN ARRAY MAYBE
        // THAT WAY IF FALSE, CAN JUST END, BUT THERE WOULD STILL BE SOME TRICKY, INELEGANT STUFF WITH THAT TOO
        if (skip_conn) {
            commands_vector.at(i).erase(commands_vector.at(i).begin());
            skip_conn = false;
        }

        // TEST REMOVE
    for (int u = 0; u < commands_vector.size(); u++) {
        for (int j = 0; j < commands_vector.at(u).size(); j++) {
            std::cout << commands_vector.at(u).at(j);
        }
    } std::cout << "\n\n" << std::endl;

        // Constructs new single command instance, passing in the current command in the form of a vector of strings
        SingleCom* single = new SingleCom(commands_vector.at(i));

        bool exec_success = single->execute();

        // TEST REMOVE
        //std:: cout << "\n SINGLE->EXECUTE = " << exec_failed << std::endl;

        // If single runs "exit", exit.
        if (single->exit) {
            this->exit = true;
            return false;
        }


        // && case
        // If there are more commands and the current command returned true, proceed to next command
        // If the current command returned false and the next command begins with &&, stop executing
        if (i + 1 < commands_vector.size() && commands_vector.at(i + 1).at(0) == "&&") {
            if (!exec_success) {
                // TEST REMOVE
                std::cout << "&& case found, !exec_success. setting false and breaking" <<  std::endl;


                continue_exec = false;


                // TEST REMOVE
                std::cout << "still within && case; continue_exec = " << continue_exec << std::endl;
                std::cout << "Returning false now.\n" << std::endl;
                this->success = false;
                return false;
            }
            else {
                skip_conn = true;
            }

            // TEST REMOVE
            std::cout << "end of if; continue_exec = " << continue_exec << std::endl;


            /* 
            if (!continue_exec) {
            return false;
            }
*/
       }

        // || case
        // If there are more commands and the current command returned false, proceed to next command
        // If the current command returned true and the next command begins with ||, stop executing
        else if (i + 1 < commands_vector.size() && commands_vector.at(i + 1).at(0) == "||") {
            if (!exec_success) {
                this->success = false;
                //continue_exec = false;
                return false;
            }
            else {
                skip_conn = true;
            }
        }


        // TEST REMOVE
        //std::cout << "this->success = " << this->success << std::endl;
        /*if (!this->success) {
            return false;
        }*/

        // TEST REMOVE
        //std::cout << "End of while loop BEFORE COUNTER++ AND DELETE SINGLE. continue_exec is: " << continue_exec << "\n" << std::endl;

        // Is this how we avoid memory leaks?
        //delete single;


        // TEST REMOVE
        //std::cout << "END OF WHILE LOOP. continue_exec: " << continue_exec << "\n" << std::endl;
    }

    // TEST 

    return continue_exec;
}
