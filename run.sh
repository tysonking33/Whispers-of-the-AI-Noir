#!/bin/bash

clear

# Compile the code with the proper include path
g++ -std=c++17 -Wall -Wextra -Werror -I./includes ./source/*.cpp -o main.exe

# Run the compiled executable
./main.exe
