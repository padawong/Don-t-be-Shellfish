#Assignment 4:

Chaining does not work at all.
Single redirections/pipes work fine
Error handling for single redir/pipes seems to also be fine
Seems to integrate fine with old functionality

One new file src/redir_pipe.cpp which deals with all redirection and piping

Once again, struggling to tag
STILL TRYING BUT IT'S NOT WORKING

# Hw3
Assignment 3: README
 
KNOWN BUGS: exit doesn't work very well. When it's chained with commands it doesn't seem to work when the commands are too long
If a valid execvp command is followed by bad variable, it won't flag as false
Surely there are more; will update

Not enough test cases


***Summary:*** 
    So far, we have completed all the requirements for assignment 3. Implementing the Composite pattern, we:

 1. Initialized the shell (with the extra credit requirements done as well)
 2. Interpreted and executed the commands that are inputted 
 3. Parsed commands and decided how/when to terminate 
 4. Added precedence operators
 5. Implemented testing for whether or not a given file path is valid. 


## main.cpp
 Our **main.cpp** prompts user to enter a string of commands, which is received and stored via **getline()**, and is used to create a new object of type **CompositeCom**. CompositeCom has a **parse()** function that is used to chop up and execute individual commands within the line of commands we received from the user. This is all encompassed within a do-while loop, taking in commands until the user enters an exit, which is caught in **parse()** and sets our do-while loop's condition to false to break. 
    

## CompositeCom

 Once we have passed the user inputted command into Composite command, we user delimiters to create a vector of vectors comprised only of the commands and the connectors. At each vector within the larger vector, the first element is the connector.  
 - parse()
	 - Any number of commands are divided up with a delimiter 
 - execute()
	 - Passes each individual command to SingleCom


## SingleCom

The SingleCom class actually executes each one of the commands that it receives in CompositeCom, utilizing **execvp** to handle all the commands. We fork to handle parent and child commands, so that the parent waits to execute after the child. 

Returns true in the event of each user command being executed properly, else false if either or the parent of the child does not. We use **pid** in order to wait for any subprocesses to finish before executing the ones at hand. 

## TestCom

The TestCom class simply utilizes stat() and two of its macros to verify whether the passed in vector contains a valid file path or not. It was much simpler to implement this as a child of SingleCom rather than a child of Commands, as in that case, we would be able to use that single command string containing just the test to run through and validate. 


## Bugs? 
We came across one bug in the exec, within the while loop. We initially used a true false flag as part of the while loop condition to break on a false. Somewhere between, out flag kept getting changed, and we couldn't figure out why this was happening, even if we tried debugging using **cout** flags to pinpoint where in the code the switch was occurring. We decided to change up our approach. 

List of bugs we came across:
- Why exit had to be entered N times in order for it to actually exit
  + In fact, if we input "garbage_input && echo hi", the second command will not happen (as expected) UNTIL "exit" is called once, then "echo hi" occurs. Exit successful on second "exit" call.
- Ending a command with a semicolon throws an error regardless of command length.
- Empty command NEWLINE results in failure 
- (Not exactly a bug) Couldn't figure out how to test/verify the execution of commands, so instead we just test the parsing function and the bool return of a valid command
- Came across a lot of issues regarding the parenthesis, a lot of cases work, but some cases fail, which we found odd as they mirrored previous test cases which passed successfully 
- Pressing enter results in a seg fault, and exit is similarly causing some problems (probably something to do with how we assign its boolean value in one of the classes) 
