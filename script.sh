#!/bin/bash

# 4. Perform dos2unix on files in specified directories
cd testOutput
dos2unix *
cd ..

cd testOutput2
dos2unix *
cd ..

cd testOutput3
dos2unix *
cd ..
