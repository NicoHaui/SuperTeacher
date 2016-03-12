#!/usr/bin/env bash

brew update &&
brew install asciidoc &&
brew install sdl2 &&

curl -O https://github.com/google/googletest/archive/release-1.7.0.zip &&
unzip googletest-release-1.7.0.zip && cd googletest-release-1.7.0 &&
mkdir build && cd build &&
cmake .. && make &&
sudo cp -r ../include/gtest /usr/local/include/ &&
sudo cp lib*.a /usr/local/lib
