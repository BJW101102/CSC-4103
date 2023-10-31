// This is a standalone test.

#include <stdio.h>
#include <unistd.h>
#include "fileio.h"

int main(int argc, char *argv[]) {
  File f1, f2;
  unlink("one.dat");
  unlink("two.dat");
  f1=open_file("one.dat");
  fs_print_error();
  write_file_at(f1, "ELF", 3, BEGINNING_OF_FILE, 1L);
  fs_print_error();
  f2=open_file("two.dat");
  fs_print_error();
  write_file_at(f2, "AB", 2, BEGINNING_OF_FILE, 0L);
  fs_print_error();
  write_file_at(f1, "\x7F", 1, BEGINNING_OF_FILE, 0L);
  fs_print_error();
  close_file(f1);
  fs_print_error();
  close_file(f2);
  fs_print_error();
  return 0;
}
  

  

