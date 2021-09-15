gcc -c foo.c
# https://www.diigo.com/user/chenls/b/605498372

echo -e "\nreadelf -h foo.o"
readelf -h foo.o
echo -e "\nreadelf -S foo.o"
readelf -S foo.o
