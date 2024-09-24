echo
./generate-release.sh
echo 
echo "[/][ANY] to run valgrind for release executable . . ."
export DEBUGINFOD_URLS=https://debuginfod.archlinux.org 
read
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./../Release/bin/Release
echo
echo "[/][ANY] to exit memcheck-release script . . ."
read
clear