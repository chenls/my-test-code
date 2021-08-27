optimized:
	gcc -ffunction-sections -fdata-sections -c main2.c
	gcc -Wl,-gc-sections -o test_optimized main2.o

normal:
	gcc -c main2.c
	gcc -o test_normal main2.o

clean:
	-@rm *.o test_normal test_optimized
