// do NOT delete "badelf.dat before running this test.  Run this test
// *after* rw-test-1.

#include <stdio.h>
#include <unistd.h>
#include "fileio.h"

int main(int argc, char *argv[]) {
  File f;
  
  f=open_file("badelf.dat");
  fs_print_error();
  write_file_at(f, "ELF", 3, END_OF_FILE, 0L);
  fs_print_error();
  close_file(f);
  fs_print_error();
  return 0;
}
  

  

