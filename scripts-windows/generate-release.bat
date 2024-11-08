@echo off
gcc -o ../Release/bin/Release.exe ../main.c -O3 "../Source Files/stdlib/bit.c" "../Source Files/stdlib/boolean.c" "../Source Files/stdlib/common.c" "../Source Files/stdlib/dArray.c" "../Source Files/stdlib/file.c" "../Source Files/stdlib/math.c" "../Source Files/stdlib/matrix.c" "../Source Files/stdlib/memory.c" "../Source Files/stdlib/hash.c" "../Source Files/stdlib/hashtable.c" "../Source Files/stdlib/linkedList.c" "../Source Files/stdlib/queue.c" "../Source Files/stdlib/stack.c" "../Source Files/stdlib/string.c" "../Source Files/stdlib/timetest.c" "../Source Files/stdlib/vector.c"
echo.
echo [+] Built project . . .
echo.
set /p DUMMY=[/][ENTER] to close this console . . .
exit
