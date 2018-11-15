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
    //EXPECT_EQ(, );
    

}


TEST(EchoTest, ConnectorCommands){
    //EXPECT_EQ();

}    


TEST(EchoTest, CommentCommands){
    //EXPECT_EQ();

}


TEST(EchoTest, ExitCommands){
    //EXPECT_EQ();

}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
