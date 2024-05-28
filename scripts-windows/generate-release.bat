@echo off
gcc -o ../Release/Release.exe ../main.c -O3 "../Source Files/stdlib/dArray.c" "../Source Files/stdlib/file.c" "../Source Files/stdlib/string.c" "../Source Files/stdlib/math.c" "../Source Files/stdlib/matrix.c"
echo.
echo [+] Built project . . .
echo.
set /p DUMMY=[/][ENTER] to close this console . . .
exit