clear
dir=$(dirname $(readlink -f "$0"))
cd $dir

gcc -c main.c
g++ main.o MyIn.cpp MyLib.cpp
./a.out

cd - &>/dev/null
