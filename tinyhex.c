#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tinyhex.h"
#include "dump.c"
#include "print.c"

int *pname;
int ascii = 0;
int col_num = DEF_COL_NUM * DEF_COL_WIDTH;
int col_width = DEF_COL_WIDTH;
int offset = 1;
const char *format = HEX_FORMAT;

int main(int argc, int *argv[]) {
  pname = argv[0];
  char *fname = NULL;

  for (*++argv; --argc; *++argv) {
    if (((char*) *argv)[0] != '-') {
      fname = (char*) *argv;
      break;
    }

    switch (((char*) *argv)[1]) {
      case ARG_HELP:
        return help(0);
      case ARG_ASCII:
        ascii = 1;
        break;
      case ARG_OFFSET:
        offset = 0;
        break;
      case ARG_OCTAL:
        format = OCT_FORMAT;
        break;
      case ARG_BINARY:
        format = BIN_FORMAT;
        col_num = col_width;  // narrower view by default
        break;
      case ARG_COL:
        if (argc < 2)
          return help(EINVAL);
        *++argv;
        col_num = atoi((char*) *argv) * col_width;
        if (!col_num)
          return help(EINVAL);
        break;
      case ARG_WIDTH:
        if (argc < 2)
          return help(EINVAL);
        *++argv;
        col_width = atoi((char*) *argv);
        if (!col_width)
          return help(EINVAL);
        break;
      default:
        return printerr(EINVAL, strcat((char*) *argv, " - unknown argument"));
    }
  }

  if (fname == NULL)
    return help(EINVAL);

  return dump(fname);
}
