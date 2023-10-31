#include <stdio.h>
#include <unistd.h>
#include "fileio.h"

int main(int argc, char *argv[]) {
    File f;
  unlink("current.dat");
  f=open_file("current.dat");
  fs_print_error();

write_file_at(f, "B", 1, BEGINNING_OF_FILE, 0L);
    write_file_at(f, "R", 1, CURRENT_POSITION, 0L);
    write_file_at(f, "A", 1, CURRENT_POSITION, 0L);
    write_file_at(f, "N", 1, CURRENT_POSITION, 0L);
    write_file_at(f, "\x7F", 1, CURRENT_POSITION, -4L);
    write_file_at(f, "E", 1, CURRENT_POSITION, -3);
    //fs_print_error();
    write_file_at(f, "L", 1, CURRENT_POSITION, -2L);
    //write_file_at(f, "F", 1, CURRENT_POSITION, -1L);
    //fs_print_error();
    return 0;
}