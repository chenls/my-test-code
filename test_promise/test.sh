dir=$(dirname $(readlink -f "$0"))
cd "${dir}" || exit 1
g++ -std=c++11 -g -O0 main.cpp -lpthread -o main 
# ./main