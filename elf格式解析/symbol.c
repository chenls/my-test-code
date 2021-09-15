/// global val
extern int g_a;
int g_b;
int g_c = 0;
int g_d = 10;
 
 
/// static val
static int s_a;
static int s_b = 0;
static int s_c = 20;
 
 
extern int boo(int);
 
void func() {
    static int l_s_a;
    static int l_s_b = 0;
    static int l_s_c = 30;
 
    g_a = 66;
    int x = 10;
    int y = 20;
    int z = x + y;
    int result = 0;
    result = boo(z);
}
 
static void foo() {
    boo(10);
}