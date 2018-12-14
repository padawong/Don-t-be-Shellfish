#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <string>
#include "../src/headers/CompositeCom.h"
#include "../src/headers/paren.h"

// Tests tokenize function which takes a string of input and deliminates " " and "\n" and turns it into a vector of strings
TEST(EchoTest, tokenize) {
    std::string test_string;
    test_string = "echo 1 && ((echo 2; echo 3) || echo 4)";
    
    CompositeCom* test_com = new CompositeCom(test_string);
    test_com->tokenize();

    EXPECT_EQ("echo", test_com->commands_vect.at(0));
    EXPECT_EQ("1", test_com->commands_vect.at(1));
    EXPECT_EQ("&&", test_com->commands_vect.at(2));
    EXPECT_EQ("((echo", test_com->commands_vect.at(3));
    EXPECT_EQ("2;", test_com->commands_vect.at(4));
    EXPECT_EQ("echo", test_com->commands_vect.at(5));
    EXPECT_EQ("3)", test_com->commands_vect.at(6));
    EXPECT_EQ("||", test_com->commands_vect.at(7));
    EXPECT_EQ("echo", test_com->commands_vect.at(8));
    EXPECT_EQ("4)", test_com->commands_vect.at(9));
    EXPECT_EQ(10, test_com->commands_vect.size());

    delete test_com;
}

TEST(EchoTest, bashTestOne){
    char* test_val[4];
    test_val[0] = "./test"; 
    test_val[1] = "cat"; 
    test_val[2] = "<";
    test_val[3] = "test.txt";

    char* output_val[3];

    ifstream dataFile("test.txt");
    for(int i = 0; i < 3; i++){

        while (!dataFile.fail() && !dataFile().eof){
            dataFile >> output_val[i];
        }

    }

    EXPECT_EQ("", output_val[0]);
}


TEST(EchoTest, bashTestTwo){
    char* test_val[5];
    test_val[0] = "./test"; 
    test_val[1] = "echo"; 
    test_val[2] = "hello";
    test_val[3] = ">";
    test_val[4] = "test.txt";
    //EXPECT_EQ("hello world", echo(3,test_val));

    char* output_val[3];

    ifstream dataFile("test.txt");
    for(int i = 0; i < 3; i++){

        while (!dataFile.fail() && !dataFile().eof){
            dataFile >> output_val[i];
        }

    }

    EXPECT_EQ("hello", output_val[0]);
}


TEST(EchoTest, bashTestThree){
    char* test_val[6];
    test_val[0] = "./test"; 
    test_val[1] = "echo"; 
    test_val[2] = "line";
    test_val[3] = "2";
    test_val[4] = ">>";
    test_val[5] = "test.txt";
    //EXPECT_EQ("hello world", echo(3,test_val));
}

TEST(EchoTest, bashTestFour){
    char* test_val[3];
    test_val[0] = "./test"; 
    test_val[1] = "cat"; 
    test_val[2] = "test.txt";
    test_val[3] = "|";
    test_val[4] = "tr";
    test_val[5] = "a-z";
    test_val[6] = "A-Z";
    //EXPECT_EQ("hello world", echo(3,test_val));
}









// Tests that parse correctly generates first_cmd->right
// Does so by checking that first_cmd->right->commands_vect holds the command
TEST(EchoTest, parse_single) {
    std::string test_string;
    test_string = "test -e ./src";
    
    CompositeCom* test_com = new CompositeCom(test_string);
    test_com->tokenize();
    test_com->parse(test_com->commands_vect);

    // test_com->first_cmd->right->commands_vect should have "test", "-e", "src"
    // I know the path is ugly... shhhhhhh...
    EXPECT_EQ("test", test_com->first_cmd->right->commands_vect.at(0));
    EXPECT_EQ("-e", test_com->first_cmd->right->commands_vect.at(1));
    EXPECT_EQ("./src", test_com->first_cmd->right->commands_vect.at(2));
    EXPECT_EQ(3, test_com->first_cmd->right->commands_vect.size());

    delete test_com;
}
/*
// Tests that parse correctly generates a string of commands containing nested parentheses 
// Does so by checking that the FIRST connector (&&) holds the expected command on the right
TEST(EchoTest, parse_oneone__parentheses) {
    std::string test_string;
    test_string = "(echo hello)";
    
    CompositeCom* test_com = new CompositeCom(test_string);
    test_com->tokenize();
    test_com->parse(test_com->commands_vect);
    
    Paren* in_parenth = test_com->first_cmd->right;
    std::vector<std::string> commands = in_parenth->inner->first_cmd->commands_vect;
    
    EXPECT_EQ("echo", commands.at(0));
    EXPECT_EQ("hello", test_com->commands_vect.at(1));
    EXPECT_EQ(2, test_com->commands_vect.size());


    delete test_com;
}
*/
/*
// Tests that parse correctly generates a string of commands containing nested parentheses 
// Does so by checking that the FIRST connector (&&) holds the expected command on the right
TEST(EchoTest, parse_parentheses) {
    std::string test_string;
    test_string = "echo 1 && (echo 2; echo 3) || echo 4))";
    
    CompositeCom* test_com = new CompositeCom(test_string);
    test_com->tokenize();
    test_com->parse(test_com->commands_vect);
    
    // Testing first connector's right command
    // Third connector is &&, right should be a parens object containing two commands connected by ||
    // Testing that "echo 3" is where it is expected to be

    //Commands* outside_parentheses = test_com->first_cmd->next;
    //Commands* inner_parentheses = outside_parentheses->inner->first_cmd;
    // outside_parentheses->inner->first_cmd->next = echo 4 command
    //Commands* inner_p_cmd1 = inner_parentheses->inner->first_cmd->right->;
    Paren* outer_par = test_com->first_cmd->next;
    Paren* inner_par = outer_par->inner->first_cmd->right;
    
    std::vector<std::string> commands = inner_par->inner->first_cmd->right->commands_vect;
    
    EXPECT_EQ("echo", commands.at(0));
    EXPECT_EQ("2", test_com->commands_vect.at(1));
    EXPECT_EQ(2, test_com->commands_vect.size());


    delete test_com;
}

TEST(EchoTest, composite_comment_parse) {
    std::string test_string;
    test_string = "ls && echo hi; echo please_give_us_100_percent #hashtag just joking #hashtag not joking at all";
    
    CompositeCom* test_com = new CompositeCom(test_string);
    test_com->parse();
    
    // comm1: "ls"
    std::vector<std::string> comm1 = test_com->commands_vector.at(0);

    // comm2: "&&" "echo" "hi
    // note: the semicolon is dropped and not saved anywhere
    std::vector<std::string> comm2 = test_com->commands_vector.at(1);

    // comm3: "echo" "please_give_us_100_percent"
    std::vector<std::string> comm3 = test_com->commands_vector.at(2);


    EXPECT_EQ("ls", comm1.at(0));
    EXPECT_EQ(1, comm1.size());

    EXPECT_EQ("&&", comm2.at(0));
    EXPECT_EQ("echo", comm2.at(1));
    EXPECT_EQ("hi", comm2.at(2));
    EXPECT_EQ(3, comm2.size());

    EXPECT_EQ("echo", comm3.at(0));
    EXPECT_EQ("please_give_us_100_percent", comm3.at(1));
    EXPECT_EQ(2, comm3.size());
    
    EXPECT_EQ(3, test_com->commands_vector.size());

    delete test_com;
}

TEST(EchoTest, valid_command) {
    std::string test_string;
    test_string = "echo Hello please grade generously :D";

    CompositeCom* test_com = new CompositeCom(test_string);
    test_com->parse();

    bool success = test_com->execute();

    EXPECT_EQ(true, success);
}
*/
int main(int argc, char **argv) {
//  ARGV_IN = argv;
    
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
