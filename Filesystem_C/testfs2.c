#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"



int main(int argc, char *argv[]) {

  File seekFile = create_file("seek_test_file");
  printf("ret from create_file(\"seek_test_file\") = %p\n", seekFile);
  fs_print_error();

  
  int writeResult = write_file(seekFile, "abcdef", strlen("abcdef"));
  printf("ret from write_file(seekFile, \"abcdef\", strlen(\"abcdef\")) = %d\n", writeResult);
  fs_print_error();

  
  printf("Seeking to position 2.\n");
  seek_file(seekFile, 2);
  fs_print_error();

  close_file(seekFile);
  printf("Executed close_file(seekFile).\n");
  fs_print_error();

  return 0;
}