extern int a;
 
int b;
int b1 = 0;
int b2 = 1;
 
static int c1;
static int c2 = 0;
static int c3 = 1;
 
__attribute__((weak)) int d1;
__attribute__((weak)) int d2 = 0;
__attribute__((weak)) int d3 = 1;
 
 
void foo() {
    /// 故意用一下。不用的可能会被编译器优化掉
    a = 10;
}