// This is a standalone test.
#include <stdio.h>
#include <unistd.h>
#include "fileio.h"

int main(int argc, char *argv[]) {
  File f;
  unlink("another.dat");
  f=open_file("another.dat");
  fs_print_error();
  write_file_at(f, "HELLOTHERE", strlen("HELLOTHERE"), BEGINNING_OF_FILE, 0L);
  fs_print_error();
  write_file_at(f, "F", 1, END_OF_FILE, -7L);
  fs_print_error();
  write_file_at(f, "L", 1, END_OF_FILE, -8L);
  fs_print_error();
  write_file_at(f, "E", 1, END_OF_FILE, -9L);
  fs_print_error();
  write_file_at(f, "\x7F", 1, END_OF_FILE, -10L);
  fs_print_error();
  close_file(f);
  fs_print_error();
  return 0;
}
  

  

