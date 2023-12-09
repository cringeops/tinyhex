#include "tinyhex.h"

extern int col_num;

int dump(const char *fname) {
  FILE *fp = fopen(fname, "r");
  if (fp == NULL)
    return printerr(errno, 0);

  char buf[col_num];

  fseek(fp, 0L, SEEK_END);
  long fsz = ftell(fp);
  rewind(fp);

  for (long pos = 0; pos < fsz; pos+=col_num) {
    fread(buf, col_num, 1, fp);
    print_dump(buf);
  }

  fclose(fp);
  return 0;
}
