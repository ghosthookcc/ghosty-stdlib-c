@echo off
start cmd.exe /c generate-release.bat
cls
set /p DUMMY=[/][ENTER] to run program in release mode . . .
cls
..\Release\Release.exe