#!/bin/sh
clear
echo
echo "[+] Building project in release mode . . ."
echo

cd "../Source Files/stdlib"
SPATHS=$(find . -type f -name "*.c")
SOURCE=""
for path in $SPATHS; do
	SOURCE="$SOURCE $path"
done

WARNINGS=""
TARGET="Release"
GCC_OPT="-O3 -ffast-math"
FLAGS=""
OUT="../../Release/bin/"$TARGET

gcc $WARNINGS $GCC_OPT $FLAGS ../../main.c $SOURCE -I./"../../Header\ Files/stdlib/" -o $OUT
cd "../../scripts-linux"
echo "[/][ANY] to close this console . . ."
read
