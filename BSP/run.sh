#!/bin/bash

clear

# Compile the code with the proper include path
g++ -std=c++17 -Wall -Wextra -Werror bsp_main.cpp -o main.exe

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Run the compiled executable
    ./main.exe
else
    echo -e "\033[31mCompilation failed. Fix errors and try again.\033[0m"
fi
