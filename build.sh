#!/bin/bash

INSTALL_DIR=$1
BUILD_DIR=build


if [ ! -d "$BUILD_DIR"]; then
    echo "not exist dir $BUILD_DIR"
else
    rm -rf "$BUILD_DIR"
    mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR"
cmake -DCMAKE_TOOLCHAIN_FILE="../CrossCompile.cmake" -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR/../  ..
make
make install


