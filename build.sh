#!/bin/sh

CC=clang
CFLAGS="-g -O0 -std=c11 -Wextra -Wno-incompatible-library-redeclaration -Wno-sign-compare -Wno-unused-parameter -Wno-builtin-requires-header -femit-all-decls -Xclang -target-feature -Xclang +amx-int8"
SRC=../build.c

mkdir -p build
cd build
$CC $SRC -o cgame $CFLAGS $1
cd ..
