@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
echo.
echo [+] Call to open visual studio developer cmd complete . . .
echo.
cl ../main.c "../Source Files/stdlib/dArray.c" "../Source Files/stdlib/file.c" "../Source Files/stdlib/string.c" "../Source Files/stdlib/math.c" "../Source Files/stdlib/matrix.c" "../Source Files/stdlib/hash.c" "../Source Files/stdlib/hashtable.c" "../Source Files/stdlib/linkedList.c" "../Source Files/stdlib/queue.c" "../Source Files/stdlib/stack.c" "../Source Files/stdlib/vector.c" /fsanitize=address /Zi /Od /Fe:../Debug/bin/Debug.exe /Fo:../Debug/obj/ /Fd:../Debug/pdb/Debug.pdb
echo.
echo [+] Built project . . .
echo.
set /p DUMMY=[/][ENTER] to close this console . . .
exit
