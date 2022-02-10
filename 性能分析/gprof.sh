sudo apt install graphviz
python3 -m pip install --user gprof2dot

gcc -pg -ggdb3 -O3 -std=c99 -Wall -Wextra -pedantic -o main-O3.out main.c
time ./main-O3.out 10000
gprof main-O3.out > main-O3.gprof
gprof2dot < main-O3.gprof | dot -Tsvg -o output-O3.svg

gcc -pg -ggdb3 -O0 -std=c99 -Wall -Wextra -pedantic -o main-O0.out main.c
time ./main-O0.out 10000
gprof main-O0.out > main-O0.gprof
gprof2dot < main-O0.gprof | dot -Tsvg -o output-O0.svg

gprof -b main-O0.out
