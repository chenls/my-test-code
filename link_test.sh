clear
gcc -c mylib1.c -o mylib1.o
gcc -c mylib2.c -o mylib2.o
gcc -c mylib3.c -o mylib3.o

ar rc mylib.a mylib1.o mylib2.o
ar rc mylib2.a mylib3.o

gcc main.c mylib2.a mylib.a -o link_test -Wl,-Map=link_test.map

./link_test
