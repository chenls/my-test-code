#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int BKDRHash(const char *p_str) {
  unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
  unsigned int hash = 0;

  while (*p_str) {
    printf("%c\n", *p_str);
    hash = hash * seed + (*p_str++);
  }
  printf("chenls BKDRHash hash = %u\n", hash);
  return (hash & 0x7FFFFFFF);
}

unsigned int str_hash_1(const char *s) {
  unsigned char *p = (unsigned char *)s;
  unsigned int hash = 0;
  unsigned int seed = 131; // 3,5,7,9,...,etc奇数
  unsigned int nIndex = 0;
  unsigned int nLen = strlen((char *)p);
  while (*p) {
    printf("%c\n", *p);
    hash = hash + pow(seed, nLen - nIndex - 1) * (*p);
    ++p;
    nIndex++;
  }
  printf("chenls str_hash_1 hash = %u\n", hash);
  return hash;
}

int main(int argc, char const *argv[]) {
  char name[128] = "abc";

  str_hash_1(name);
  BKDRHash(name);

  return 0;
}
