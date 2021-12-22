//来源：公众号【编程珠玑】
//网站：https://www.yanbinghu.com
#ifdef MYMOCK //只有MYMOCK编译选项是，这段代码才会编译进去
#include <stdio.h>
#include <stdlib.h>
void *__real_malloc(size_t size); //注意声明
/*打桩函数*/
void *__wrap_malloc(size_t size) {
  void *ptr = __real_malloc(size); //最后会被解析成malloc
  printf("ptr is %p\n", ptr);
  return ptr;
}
#endif