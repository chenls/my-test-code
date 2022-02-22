dir=$(dirname $(readlink -f "$0"))
cd "${dir}" || exit 1
g++ -std=c++11 main.cpp -lpthread -o main 
./main