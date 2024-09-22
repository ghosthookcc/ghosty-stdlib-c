#!/bin/sh
clear
echo
echo "[+] Building project in debug mode . . ."
echo

cd "../Source Files/stdlib"
SPATHS=$(find . -type f -name "*.c")
SOURCE=""
for path in $SPATHS; do
	SOURCE="$SOURCE $path"
done

WARNINGS="-Wall -Wpedantic"
TARGET="Debug"
GCC_OPT="-O0"
FLAGS="-g -LDEBUG"
OUT="../../Debug/bin/"$TARGET

gcc $WARNINGS $GCC_OPT $FLAGS ../../main.c $SOURCE -I./"../../Header\ Files/stdlib/" -o $OUT
cd "../../scripts-linux"
echo
echo "[/][ANY] to close this console . . ."
read
clear
