CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
	./src/main.cpp
    ./src/Commands.cpp
    ./src/CompositeCom.cpp
    ./src/SingleCom.cpp
    ./src/TestCom.cpp
    ./src/and_op.cpp
    ./src/or_op.cpp
    ./src/semi_op.cpp
    ./src/paren.cpp
    ./src/redir.cpp
)

ADD_EXECUTABLE(test
    ./tests/test.cpp
    ./src/Commands.cpp
    ./src/CompositeCom.cpp
    ./src/SingleCom.cpp
    ./src/TestCom.cpp
    ./src/and_op.cpp
    ./src/or_op.cpp
    ./src/semi_op.cpp
    ./src/paren.cpp
    ./src/redir.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)

