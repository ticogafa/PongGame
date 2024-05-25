#!/bin/bash

# Compile the code
gcc -I./include src/*.c -o PongGame

# Check if the compilation was successful
if [ $? -eq 0 ]; then
  # Run the game
  ./PongGame
else
  echo "Compilation failed. Please check for errors."
fi