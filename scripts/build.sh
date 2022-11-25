#!/bin/bash
####################################################
# This script builds project
####################################################
mkdir bin
cd bin
cmake ..
make -j8