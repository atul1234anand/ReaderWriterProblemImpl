#!/bin/bash

./clean.sh
mkdir -p build
cd build
cmake ..
make -j4
make install DESTDIR="../install-dir"
cd -
