#!/bin/bash

rm -fr build
mkdir build
cd build
cmake .. -DCMAKE_C_COMPILER="/opt/arm-anykav500-eabi/bin/arm-anykav500-eabi-gcc"
make
