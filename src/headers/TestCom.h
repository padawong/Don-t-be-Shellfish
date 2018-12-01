#ifndef TESTCOM_H
#define TESTCOM_H

#include "Commands.h"
#include <string>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <sys/stat.h>
#include "SingleCom.h"

using namespace std;

class TestCom : public SingleCom {  
    public:
        TestCom();
        TestCom(std::vector<std::string> &cmd_v);
            
        bool testLine();
};

#endif //TESTCOM_H
