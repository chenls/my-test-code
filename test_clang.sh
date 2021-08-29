# 二进制代码形式
clang -emit-llvm -c main_clang.c -o main_clang.bc

# 可读文本代码形式
clang -S -emit-llvm -c main_clang.c -o main_clang.ll