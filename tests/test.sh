#!/bin/sh

INPUTS=("echo this is a new file > new_file.txt" "cat < new_file.txt" "echo overwriting > new_file.txt" "cat < new_file.txt" "echo appending >> new_file.txt" "echo new_file.txt | tr a-z A-Z")

./rshell 
${INPUTS[0]} 
${INPUTS[1]} 
${INPUTS[2]} 
${INPUTS[3]} 
${INPUTS[4]} 
${INPUTS[5]} 
