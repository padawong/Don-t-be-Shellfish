#include "gtest/gtest.h"
#include <iostream>


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




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
