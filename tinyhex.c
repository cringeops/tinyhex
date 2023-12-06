#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define COL            4
#define DEF_COL_NUM    COL * 6
#define ON             1
#define OFF            0

#define ARG_HELP       "-h"
#define ARG_ASCII      "-C"

int help(void);
int dump(const char *);
int printerr(int);
void print_dump(char *);

int *pname;
int ascii = OFF;
int col_num = DEF_COL_NUM;

int help(void) {
  printf(
    "%s: [FLAGS] FILENAME\n"
    "dump file as hex\n"
    "flags:\n"
    "\t-h - show this help\n"
    "\t-cN - columns, i.e. -c4\n"
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
  printf("%08x: ", row_count+=COL_NUM);
  for (int i = 0; i < COL_NUM; i++) {
    if (i && !(i % 4))
      printf(" ");
    printf("%02x ", (unsigned char) buf[i]);
  }

  if (ascii) {
    printf(" | ");
    for (int i = 0; i < COL_NUM; i++)
      printf("%c", (unsigned char) (isprint(buf[i]) && (buf[i] != '\n') ? buf[i] : ' '));
    printf("%2c", '|');
  }

  printf("\n");
}

int dump(const char *fname) {
  FILE *fp = fopen(fname, "r");
  if (fp == NULL)
    return printerr(errno);

  char buf[24];

  fseek(fp, 0L, SEEK_END);
  long fsz = ftell(fp);
  rewind(fp);

  for (long pos = 0; pos < fsz; pos+=COL_NUM) {
    fread(buf, COL_NUM, 1, fp);
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
    ascii = ON;
  else {
    printf("%s: unknown flag %s\n", pname, flag);
    return 1;
  }
  return dump(fname);
}
