//////////////////////////////////////////////////////////////////////
// Intentionally flawed system call library that implements         //
// (unfortunately, not) "safe" file I/O, which "disallows" writing  //
// "\x7F""ELF" at the beginning of a file.                          //
// Tweaks by A. Ali-Gombe  8/2022                                   //
// Written by Golden G. Richard III (@nolaforensix), 6/2022.        //
//                                                                  //
// Props to Brian Hay for the idea, based on a similar exercise he  //
// used in a training exercise.                                     //
//////////////////////////////////////////////////////////////////////

//Brandon Walton

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"

FSError fserror;
char trckArray[4] = {0};
long total_bytes;
long current = 0;
long prevCurrent = 0;

static int seek_file(File file, SeekAnchor start, long offset)
{
  if (!file || (start != BEGINNING_OF_FILE &&
                start != CURRENT_POSITION && start != END_OF_FILE))
  {
    return 0;
  }
  else
  {
    if (!fseek(file, offset, start == BEGINNING_OF_FILE ? SEEK_SET : (start == END_OF_FILE ? SEEK_END : SEEK_CUR)))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
}

File open_file(char *name)
{
  File fp;

  fserror = NONE;
  // try to open existing file
  fp = fopen(name, "r+");
  if (!fp)
  {
    // fail, fall back to creation
    fp = fopen(name, "w+");
    if (!fp)
    {
      fserror = OPEN_FAILED;
      return NULL;
    }
  }
  return fp;
}

void close_file(File file)
{
  if (file && !fclose(file))
  {
    fserror = NONE;
  }
  else
  {
    fserror = CLOSE_FAILED;
  }
}
unsigned long bytesRead;

unsigned long read_file_from(File file, void *data, unsigned long num_bytes, SeekAnchor start, long offset)
{
  unsigned long bytes_read = 0L;

  fserror = NONE;
  if (!file || !seek_file(file, start, offset))
  {
    fserror = READ_FAILED;
  }
  else
  {
    bytes_read = fread(data, 1, num_bytes, file);
    if (ferror(file))
    {
      fserror = READ_FAILED;
    }
  }
  return bytes_read;
}
long count = 0;

//Begin Checking for ILLEGAL ELF format
unsigned long write_file_at(File file, void *data, unsigned long num_bytes, SeekAnchor start, long offset)
{

  unsigned long bytes_written = 0L;
  total_bytes += num_bytes;

  fserror = NONE;
  if (!file || !seek_file(file, start, offset))
  {
    fserror = WRITE_FAILED;
  }

  (strlen(trckArray) == 4) ? (total_bytes--) : 0; // Used to avoid double counting when editing a byte
  if (total_bytes - (abs(offset)) <= 4L || strlen(trckArray) != 4)
  {
    for (int i = 0; i < num_bytes; i++)
    {
      switch (start)
      {
      case END_OF_FILE:
        trckArray[((total_bytes) - (abs(offset)))] = ((char *)data)[i];
        offset--;
        break;
      case BEGINNING_OF_FILE:
        trckArray[abs(offset)] = ((char *)data)[i];
        offset++;
        break;
      case CURRENT_POSITION:
        current = prevCurrent;
        current = (offset < 0) ? (total_bytes - abs(offset)) : current;
        trckArray[current] = ((char *)data)[i];
        current++;
        prevCurrent = current;
        break;
      }
    }
    (strlen(trckArray) > 4) ? (trckArray[4] = '\0') : 0;
  }

  bytes_written = fwrite(data, 1, num_bytes, file);
  if (bytes_written < num_bytes)
  {
    fserror = WRITE_FAILED;
  }

  fserror = (strcmp(trckArray, "\x7F"
                               "ELF") == 0)
                ? ILLEGAL_ELF
                : fserror;
  //printf("TRACKER: %s\n", trckArray);
  count++;
  return bytes_written;
}

void fs_print_error(void)
{
  printf("FS ERROR: ");
  switch (fserror)
  {
  case NONE:
    puts("NONE");
    break;
  case OPEN_FAILED:
    puts("OPEN_FAILED");
    break;
  case CLOSE_FAILED:
    puts("CLOSE_FAILED");
    break;
  case READ_FAILED:
    puts("READ_FAILED");
    break;
  case WRITE_FAILED:
    puts("WRITE_FAILED");
    break;
  case ILLEGAL_ELF:
    puts("ILLEGAL_ELF: SHAME ON YOU!");
    break;
  default:
    puts("** UNKNOWN ERROR **");
  }
}
