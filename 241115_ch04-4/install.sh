#!/bin/bash

mkdir -p build
cd build

cmake ..
make -j$(nproc)

sudo make install

cd ..
rm -r build