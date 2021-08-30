clear
rm -rf *.o *.a
gcc -c mylib1.c -o mylib1.o
gcc -c mylib2.c -o mylib2.o
ld -r mylib1.o mylib2.o -o mylib.o

gcc main.c mylib.o -o link_test -Wl,-Map=link_test.map

ls -l ./link_test
# nm ./link_test
./link_test


rm -rf *.o *.a
gcc -flto -c mylib1.c -o mylib1.o
gcc -flto -c mylib2.c -o mylib2.o
ld -flto -r mylib1.o mylib2.o -o mylib.o

gcc -flto main.c mylib.o -o link_test -Wl,-Map=link_test.map

ls -l ./link_test
nm ./link_test
./link_test



rm -rf *.o *.a
gcc -ffunction-sections -fdata-sections -c mylib1.c -o mylib1.o
gcc -ffunction-sections -fdata-sections -c mylib2.c -o mylib2.o
ld -r mylib1.o mylib2.o -o mylib.o

gcc main.c mylib.o -o link_test -Wl,-Map=link_test.map -Wl,-gc-sections


ls -l ./link_test
# nm ./link_test
./link_test



rm -rf *.o *.a
gcc -ffunction-sections -fdata-sections -c mylib1.c -o mylib1.o
gcc -ffunction-sections -fdata-sections -c mylib2.c -o mylib2.o
ld -r mylib1.o mylib2.o -o mylib.o -flto

gcc main.c mylib.o -o link_test -Wl,-Map=link_test.map -Wl,-gc-sections -flto


ls -l ./link_test
# nm ./link_test
./link_test