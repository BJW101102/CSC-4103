#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

// RUN formatfs before conducting this test!

int main(int argc, char *argv[]) {
  File readFile = create_file("read_test_file");
  printf("ret from create_file(\"read_test_file\") = %p\n", readFile);
  fs_print_error();

  close_file(readFile);
  open_file("read_test_file", READ_ONLY);

  // should succeed
  int writeResult = write_file(readFile, "hello", strlen("hello"));
  printf("ret from write_file(readFile, \"hello\", strlen(\"hello\")) = %d\n", writeResult);
  fs_print_error();

  // should succeed
  char buffer[100];
  memset(buffer, 0, 100);
  int readResult = read_file(readFile, buffer, strlen("hello"));
  printf("ret from read_file(readFile, buffer, strlen(\"hello\")) = %d\n", readResult);
  printf("buffer=\"%s\"\n", buffer);
  fs_print_error();

  // Add more test cases as needed

  close_file(readFile);
  printf("Executed close_file(readFile).\n");
  fs_print_error();

  return 0;
}