#!/bin/bash

# Step 5: Compile C++ files
g++ -g -std=c++11 -DNDEBUG -Wall *.cpp

# Step 6: Run the Python script
python3 pythonTest.py
