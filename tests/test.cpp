#include "gtest/gtest.h"
#include "op.h" 
#include "DoublePrint.h"
#include "HexPrint.h"
#include "BinaryPrint.h"
#include <iostream>
#include "DoubleFactory.h"
#include "HexFactory.h"
#include "BinaryFactory.h"
#include "factory_letter.h"
#include "VectorContainer.h"
#include "ListContainer.h"
#include "bubble.h"
#include "selection.h"

// https://stackoverflow.com/questions/4191089/how-to-unit-test-function-writing-to-stdout-stdcout

char** ARGV_IN;

TEST(EchoTest, PositiveNum){
    Op* Op1 = new Op(322);
   
    DoublePrint* doub_print = new DoublePrint(Op1->evaluate());
    HexPrint* sci_print = new HexPrint(Op1->evaluate());
    BinaryPrint* binary_print = new BinaryPrint(Op1->evaluate());

    std::ostringstream oss_double;
    doub_print->print(oss_double);
    EXPECT_EQ("322\n", oss_double.str());
    
    std::ostringstream oss_sci;
    sci_print->print(oss_sci);
    EXPECT_EQ("3.220000e+02\n", oss_sci.str());
    
    std::ostringstream oss_binary;
    binary_print->print(oss_binary);
    EXPECT_EQ("0000000000000000000000000000000000000000000000000000000101000010\n", oss_binary.str());
}

TEST(EchoTest, Zero){
    Op* Op1 = new Op(0);
   
    DoublePrint* doub_print = new DoublePrint(Op1->evaluate());
    HexPrint* sci_print = new HexPrint(Op1->evaluate());
    BinaryPrint* binary_print = new BinaryPrint(Op1->evaluate());

    std::ostringstream oss_double;
    doub_print->print(oss_double);
    EXPECT_EQ("0\n", oss_double.str());
    
    std::ostringstream oss_sci;
    sci_print->print(oss_sci);
    EXPECT_EQ("0.000000e+00\n", oss_sci.str());
    
    std::ostringstream oss_binary;
    binary_print->print(oss_binary);
    EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000000\n", oss_binary.str());
}

TEST(EchoTest, Negative){
    Op* Op1 = new Op(-2);
   
    DoublePrint* doub_print = new DoublePrint(Op1->evaluate());
    HexPrint* sci_print = new HexPrint(Op1->evaluate());
    BinaryPrint* binary_print = new BinaryPrint(Op1->evaluate());

    std::ostringstream oss_double;
    doub_print->print(oss_double);
    EXPECT_EQ("-2\n", oss_double.str());
    
    std::ostringstream oss_sci;
    sci_print->print(oss_sci);
    EXPECT_EQ("-2.000000e+00\n", oss_sci.str());
    
    std::ostringstream oss_binary;
    binary_print->print(oss_binary);
    EXPECT_EQ("1111111111111111111111111111111111111111111111111111111111111110\n", oss_binary.str());
}


TEST(EchoTest, double_factory){
    DoubleFactory* doublefactory = new DoubleFactory;
    
    BasePrint* doubleprint = doublefactory->generatePrint(14);

    std::ostringstream oss_doubleF;
    doubleprint->print(oss_doubleF);
    EXPECT_EQ("14\n" , oss_doubleF.str());
}


TEST(EchoTest, hex_factory){
    HexFactory* hexfactory = new HexFactory;
    
    BasePrint* hexprint = hexfactory->generatePrint(-2);

    std::ostringstream oss_hexF;
    hexprint->print(oss_hexF);
    EXPECT_EQ("-2.000000e+00\n" , oss_hexF.str());
}



TEST(EchoTest, binary_factory){
    BinaryFactory* binfactory = new BinaryFactory;

    BasePrint* binprint = binfactory->generatePrint(-2);

    std::ostringstream oss_binF;
    binprint->print(oss_binF);
    EXPECT_EQ("1111111111111111111111111111111111111111111111111111111111111110\n", oss_binF.str());
}

TEST(EchoTest, factory_vector){
    // Does not handle bad control line input
    char letter = *ARGV_IN[1];
    BaseFactory* doubleF = set_factory(letter);
    VectorContainer* container = new VectorContainer(new BubbleSort, doubleF);	

    Op* A = new Op(2);
	Op* B = new Op(7);
	Op* C = new Op(8);
	Op* D = new Op(5);
   
    container->add_element(A);
   	container->add_element(B);
   	container->add_element(C);
   	container->add_element(D);

   	container->sort();
	
    std::ostringstream oss_double_cont;
    container->print(oss_double_cont);
    
    if (letter == 'd')
        EXPECT_EQ("2\n5\n7\n8\n", oss_double_cont.str());
    else if (letter == 'h')
        EXPECT_EQ("2.000000e+00\n5.000000e+00\n7.000000e+00\n8.000000e+00\n", oss_double_cont.str());
    else if (letter == 'b')
        EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000010\n0000000000000000000000000000000000000000000000000000000000000101\n0000000000000000000000000000000000000000000000000000000000000111\n0000000000000000000000000000000000000000000000000000000000001000\n", oss_double_cont.str());
}

TEST(EchoTest, factory_list){
    // Does not handle bad control line input
    char letter = *ARGV_IN[1];
    BaseFactory* doubleF = set_factory(letter);
    ListContainer* container = new ListContainer(new BubbleSort, doubleF);	

    Op* A = new Op(2);
	Op* B = new Op(7);
	Op* C = new Op(8);
	Op* D = new Op(5);
   
    container->add_element(A);
   	container->add_element(B);
   	container->add_element(C);
   	container->add_element(D);

   	container->sort();
	
    std::ostringstream oss_double_cont;
    container->print(oss_double_cont);
    
    if (letter == 'd')
        EXPECT_EQ("2\n5\n7\n8\n", oss_double_cont.str());
    else if (letter == 'h')
        EXPECT_EQ("2.000000e+00\n5.000000e+00\n7.000000e+00\n8.000000e+00\n", oss_double_cont.str());
    else if (letter == 'b')
        EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000010\n0000000000000000000000000000000000000000000000000000000000000101\n0000000000000000000000000000000000000000000000000000000000000111\n0000000000000000000000000000000000000000000000000000000000001000\n", oss_double_cont.str());
}


int main(int argc, char **argv) {
  
  ARGV_IN = argv;

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
