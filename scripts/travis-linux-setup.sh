#!/usr/bin/env bash

cd /usr/src/gtest && sudo cmake . && sudo make && sudo cp *.a /usr/lib && cd $TRAVIS_BUILD_DIR;
