@echo off
start cmd.exe /c generate-debug.bat
cls
set /p DUMMY=[/][ENTER] to run program in debug mode . . .
cls
..\Debug\bin\Debug.exe