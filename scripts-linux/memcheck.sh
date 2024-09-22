echo
./generate-debug.sh
echo
./generate-release.sh 
echo
./memcheck-debug.sh 
echo 
./memcheck-release.sh
echo
echo "[/][ANY] to exit memcheck script . . ."
read 
clear