#!/bin/sh

BUILD_DIR=build/
BUILD_TYPE=Release

if [ "$1" = "debug" ]; then
	printf "%s\n" "Building in debug mode..."
	BUILD_TYPE=Debug	
fi

mkdir -p $BUILD_DIR
cd "$BUILD_DIR" || exit
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
make
