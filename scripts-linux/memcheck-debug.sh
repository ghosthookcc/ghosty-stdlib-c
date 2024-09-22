echo
./generate-debug.sh
echo 
echo "[/][ANY] to run valgrind for debug executable . . ."
export DEBUGINFOD_URLS=https://debuginfod.archlinux.org 
read
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./../Debug/bin/Debug
echo
echo "[/][ANY] to exit memcheck-debug script . . ."
read
clear