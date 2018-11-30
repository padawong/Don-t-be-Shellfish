#include "headers/and_op.h"

And_Op::And_Op() {}

bool And_Op::execute() {

    // Check for exit flag; if found, return true to exit
    if (this->prev->exit) {
        this->exit = true;
        return true;
    }

         // TEST REMOVE
        //std::cout << "within and-execute; nothing done yet" << std::endl;
        //std::cout << "this->right->commands_vect.at(0) = " << this->right-> 
  /*  std::cout << "this->prev->success = " << this->prev->success << std::endl;
    std::cout << "this->prev->right->commands_vect.at(0) = " << this->prev->right->commands_vect.at(0) << std::endl; 
*/
      
    // If previous operation returned true, run right;
    //  This entire root returns whatever value right returns 
    if (this->prev->success) {
        this->success = this->right->execute();
    }
    // If right execution is not run at all, success of entire root is false
    else {
        this->success = false;
    }
    
    // If there are more operations, continue running them
    if (this->next != NULL) {

        // TEST REMOVE
        std::cout << "within and-execute. Calling next->execute" << std::endl;

        return this->next->execute();
    }
    else {
        return this->success;
    }
}
