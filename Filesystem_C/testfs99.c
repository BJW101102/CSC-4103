#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.c"

// RUN formatfs before conducting this test!

int main(int argc, char *argv[])
{
  init_software_disk();
  File f;
  File f2;
  File f3;
  File f4;
  File f5;
  File f6;
  File f7;
  File f8;
  // File f9 = create_file("BLAH1");
  // File f10 = create_file("BLA2H");
  // File f11 = create_file("BLA4H");
  // File f12 = create_file("BLAdH");
  // File f13 = create_file("BLAvH");
  // File f14 = create_file("BLsAH");
  // File f15 = create_file("BLAaH");
  // File f16 = create_file("BLgfAH");
  // File f17 = create_file("BLAasdH");
  // File f18 = create_file("BLAHsd");
  // File f19 = create_file("BLAsdsH");

  char buf[1000];

  init_software_disk();
  f = create_file("Brandon");
  int ret;
  ret = write_file(f, "hello", strlen("hello"));
  memset(buf, 0, sizeof(buf));

  ret = read_file(f, buf, strlen("hello"));

  printf("Main buffer is: %s\n", buf);
  exit(0);

  fs_print_error();

  // close_file(f);
  // fs_print_error();
  // delete_file("Mimi");
  // fs_print_error();
  f5 = create_file("Carly");
  f6 = create_file("Venus");

  //   f = create_file("Brandon");

  // f = create_file("Silk");

  // f = create_file("Brandon");

  // f = create_file("Brandon");

  // f2 = create_file("Amelia");
  // f3 = create_file("Evelyn");
  // f4 = create_file("Bradley");
  // f5 = create_file("Clara");
  // f6 = create_file("WC");
  // f6 = create_file("Bailey");
  // f7 = create_file("Stormi");
  // f8 = create_file("Mimi");
  // File f20;
  // f20 = create_file("Messi");
  // file_exists("Banjo");
  // open_file("Banjo", READ_ONLY);

  // close_file(f);
  // f2 = create_file("Mimi");

  // for (int i = 0; i < 52349; i++)
  // {
  //   write_file(f, "A", strlen("A")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 52349; i++)
  // {
  //   write_file(f, "B", strlen("B"));
  // }

  printf("THE END\n");

  //   for (int i = 0; i < 1000; i++)
  // {
  /**/
  //   write_file(f, "Amelia", strlen("Amelia"));
  // }

  // write_file(f, "ABCDEFGHIGK", strlen("ABCDEFGHIGK"));
  // write_file(f, "ABCDEFGHIGK", strlen("ABCDEFGHIGK"));
  // write_file(f, "ABCDEFGHIGK", strlen("ABCDEFGHIGK"));

  // write_file(f, "LEBRON", strlen("LEBRON")); // write_file(f, "hello", strlen("hello"));

  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f2, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }

  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f3, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f4, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f5, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f6, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f7, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f8, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f9, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f10, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f11, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f12, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f13, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f14, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f15, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f16, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f17, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f18, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f19, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }
  // for (int i = 0; i < 13; i++)
  // {
  //   write_file(f20, "hello", strlen("hello")); // write_file(f, "hello", strlen("hello"));
  // }

  // write_file(f, "good", strlen("good"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f, "hello", strlen("hello"));
  // write_file(f2, "hello", 5);

  // open_file("Brandon", READ_ONLY);
  // file_exists("Brandon");
  // open_file("Brandon", READ_ONLY);

  // f = create_file("Brandon");
  // write_file("Brandon", "hello", strlen("hello"));
  // open_file("Brandon", READ_WRITE);
  // close_file(f);

  return 0;
}
