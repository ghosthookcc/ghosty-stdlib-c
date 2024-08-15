clear
echo
echo "[+] Building project in debug mode . . ."
echo
gcc -Wall ../main.c ../Source\ Files/stdlib/dArray.c ../Source\ Files/stdlib/file.c ../Source\ Files/stdlib/hash.c ../Source\ Files/stdlib/hashtable.c ../Source\ Files/stdlib/linkedList.c ../Source\ Files/stdlib/math.c ../Source\ Files/stdlib/matrix.c ../Source\ Files/stdlib/queue.c ../Source\ Files/stdlib/stack.c ../Source\ Files/stdlib/string.c ../Source\ Files/stdlib/vector.c -I/../Header\ Files/stdlib/ -o ../Debug/bin/Debug
echo "[/][ANY] to close this console . . ."
read
