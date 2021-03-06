#ifndef REDIR_H
#define REDIR_H

#include "SingleCom.h"
#include <string>
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <iostream>
#include <fcntl.h>

// Apparently < can have info on both sides OR just info on the right side

// It will inherit from SingleCom
class Redir : public SingleCom {
    public: 
        Redir(); 
        Redir(std::vector<std::string> &cmd_v);

        bool execute();

};

#endif // REDIR_H
