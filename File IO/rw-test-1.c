// Run rw-test-2 *after* this test.

#include <stdio.h>
#include <unistd.h>
#include "fileio.h"

int main(int argc, char *argv[])
{
  File f;
  unlink("badelf.dat");
  f = open_file("badelf.dat");
  fs_print_error();
  write_file_at(f, "B", 1, BEGINNING_OF_FILE, 0L);
  write_file_at(f, "R", 1, BEGINNING_OF_FILE, 1L);

  fseek(f, 0L, SEEK_END);
  long int fileSize = ftell(f);
  printf("FILE SIZE: %d\n", fileSize);
  fs_print_error();
  close_file(f);
  fs_print_error();
  return 0;
}
