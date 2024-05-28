@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
echo.
echo [+] Call to open visual studio developer cmd complete . . .
echo.
cl ../main.c /fsanitize=address /Zi /Fo:../Debug/Debug.obj /link /out:../Debug/Debug.exe /pdb:../Debug/Debug.pdb
echo.
echo [+] Built project . . .
echo.
set /p DUMMY=[/][ENTER] to close this console . . .
exit