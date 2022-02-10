# sudo apt install kcachegrind valgrind

rm -rf callgrind.out.*

gcc -ggdb3 -O3 -std=c99 -Wall -Wextra -pedantic -o main.out main.c

time valgrind --tool=callgrind --dump-instr=yes ./main.out 10000

kcachegrind callgrind.out.*