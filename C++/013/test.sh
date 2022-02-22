dir=$(dirname $(readlink -f "$0"))
cd "${dir}" || exit 1
g++ -std=c++14 main.cpp -lpthread -o main 
./main