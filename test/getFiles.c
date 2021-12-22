#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

void get_files(char *path) {
  struct dirent **entry_list;
  int count;
  int i;
  count = scandir(path, &entry_list, 0, alphasort);
  if (count < 0) {
    perror("scandir");
    return;
  }
  for (i = 0; i < count; i++) {
    struct dirent *entry;
    entry = entry_list[i];
    printf("%s\n", entry->d_name);
    free(entry);
  }

  printf("\n");
  free(entry_list);
}

int main(int argc, char const *argv[]) {
  get_files("/home/chenliusheng/Desktop/jiiov/image/fingerprint/image_raw/enroll/0/6354533");

  return 0;
}
