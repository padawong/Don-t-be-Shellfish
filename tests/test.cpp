#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <string>
#include "../src/headers/CompositeCom.h"


//char** ARGV_IN;

TEST(EchoTest, input_parse) {
    std::string test_string;
    test_string = "ls -a && echo cool || mkdir COOL";
    
    CompositeCom* test_com = new CompositeCom(test_string);
    test_com->parse();

    // parse() results in a vector of string vectors
    // each string vector is each single command which may contain multiple strings

    // comm1 should contain two strings: "ls" and "-a"
    std::vector<std::string> comm1 = test_com->commands_vector.at(0);

    // "&&" "echo" "cool"
    std::vector<std::string> comm2 = test_com->commands_vector.at(1);

    // "||" "mkdir" COOL"
    std::vector<std::string> comm3 = test_com->commands_vector.at(2);


    EXPECT_EQ("ls", comm1.at(0));
    EXPECT_EQ("-a", comm1.at(1));
    EXPECT_EQ("&&", comm2.at(0));
    EXPECT_EQ("echo", comm2.at(1));
    EXPECT_EQ("cool", comm2.at(2));
    EXPECT_EQ("||", comm3.at(0));
    EXPECT_EQ("mkdir", comm3.at(1));
    EXPECT_EQ("COOL", comm3.at(2));

}



/*

//The assignment specs requires us to test four overall cases:
// 1) Executing single commands
// 2) Executing commands with connectors
// 3) Executing commands with comments 
// 4) Exit commands
//
//
TEST(EchoTest, SingleCommands){
    // ls -a
    // mkdir TEST_DIR
    // ls -b
    // rm -r TEST_DIR
    // ls

    //EXPECT_EQ(, );
}


TEST(EchoTest, ConnectorCommands_1){


    //EXPECT_EQ();
}    

TEST(EchoTest, ConnectorCommands_2){
    //EXPECT_EQ();

}    

TEST(EchoTest, ConnectorCommands_3){
    //EXPECT_EQ();

}    


TEST(EchoTest, CommentCommand_1){
    //EXPECT_EQ();

}


TEST(EchoTest, CommentCommands_2){
    //EXPECT_EQ();

}


TEST(EchoTest, ExitCommands_1){
    //EXPECT_EQ();

}



TEST(EchoTest, ExitCommands_2){
    //EXPECT_EQ();

}
*/



int main(int argc, char **argv) {
//  ARGV_IN = argv;
    
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
