#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define COL            4
#define DEF_COL_NUM    COL * 6

#define ARG_HELP       "-h"
#define ARG_ASCII      "-C"

int help(void);
int dump(const char *);
int printerr(int);
void print_dump(char *);

int *pname;
int ascii = 0;
int col_num = DEF_COL_NUM;

int help(void) {
  printf(
    "%s: [FLAGS] FILENAME\n"
    "dump file as hex\n"
    "flags:\n"
    "\t-h - show this help\n"
    "\t-c N - columns\n"
    "\t-C - print ASCII\n",
    pname
  );
  return 0;
}

int printerr(int code) {
  printf("%s: error: %s\n", pname, strerror(code));
  return code;
}

void print_dump(char *buf) {
  static unsigned long row_count;
  printf("%08x: ", row_count+=col_num);
  for (int i = 0; i < col_num; i++) {
    if (i && !(i % 4))
      printf(" ");
    printf("%02x ", (unsigned char) buf[i]);
  }

  if (ascii) {
    printf(" | ");
    for (int i = 0; i < col_num; i++)
      printf("%c", (unsigned char) (isprint(buf[i]) && (buf[i] != '\n') ? buf[i] : ' '));
    printf("%2c", '|');
  }

  printf("\n");
}

int dump(const char *fname) {
  if (fname == NULL)
    return printerr(EINVAL);

  FILE *fp = fopen(fname, "r");
  if (fp == NULL)
    return printerr(errno);

  char buf[24];

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

int main(int argc, int *argv[]) {
  pname = argv[0];
  char *fname = (char*) argv[argc - 1];
  char *flag = NULL;
  if (argc == 3)
    flag = (char*) argv[1];
  else if (argc < 2 || !strcmp(fname, ARG_HELP))
    return help();

  // skip unnecessary branching
  if (!flag)
    return dump(fname);

  if (!strcmp(flag, ARG_HELP))
    return help();
  else if (!strcmp(flag, ARG_ASCII))
    ascii = 1;
  else {
    printf("%s: unknown flag %s\n", pname, flag);
    return 1;
  }
  return dump(fname);
}
