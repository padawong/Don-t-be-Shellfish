
#include <iostream>

rshell_loop(){
    char* line;
    char** args;
    int cont;

    
    do{
        cout << "$ ";
        line = rshell_read();
        args = rshell_split();
        status = rshell_execute(args);

        //idk how to clear these variables after each iteration since 
        //they are pointers
        line = null;
        args = null;
        
    } while (cont);    


}
