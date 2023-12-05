#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

#define MAX_FILE_SIZEs 65536


int main(int argc, char *argv[]) {

File f;

  f = create_file("max-size-file");
  if (f) {
    int maxFileSize = MAX_FILE_SIZEs - 1;
    char *data = (char *)malloc(MAX_FILE_SIZEs);
    memset(data, 'X', maxFileSize);
    unsigned long ret = write_file(f, data, maxFileSize);
    printf("ret from write_file(f, data, %d) = %d\n", maxFileSize, ret);
    fs_print_error();
    close_file(f);
  } else {
    printf("FAIL. Was formatfs run before this test?\n");
  }

  return 0;
}