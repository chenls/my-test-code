#include <algorithm>
#include <cstring>
#include <dirent.h>
#include <stdio.h>
#include <string>
#include <vector>

static void get_files(std::string path, std::vector<std::string> &files) {
  DIR *dir;
  struct dirent *ptr;
  if ((dir = opendir(path.c_str())) == NULL) {
    printf("Open %s dir error.\n", path.c_str());
    exit(-1);
  }

  while ((ptr = readdir(dir)) != NULL) {
    if (strcmp(ptr->d_name, ".") == 0 ||
        strcmp(ptr->d_name, "..") == 0) { // current dir OR parrent dir
      continue;
    } else if (ptr->d_type == 8) {
      std::string strFile;
      strFile = path;
      strFile += "/";
      strFile += ptr->d_name;
      files.push_back(strFile);
    } else {
      continue;
    }
  }
  closedir(dir);
  return;
}

int main(int argc, char const *argv[]) {
  char name[128] = "abc";

  std::vector<std::string> files;
  get_files("/home/chenliusheng/Desktop/jiiov/image/fingerprint/image_raw/"
            "enroll/0/635453",
            files);

  sort(files.begin(), files.end());
  for (uint32_t i = 0; i < files.size(); i++) {
    printf("file:%s\n", files[i].c_str());
  }
  return 0;
}
