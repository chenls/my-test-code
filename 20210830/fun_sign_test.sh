clang -emit-llvm -c main_clang.c -o main_clang.bc
clang++ $(llvm-config --cxxflags --ldflags --libs) fun_sign.cpp -o fun_sign -v