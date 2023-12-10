#include "tinyhex.h"

extern int *pname;
extern int ascii;
extern int col_num;
extern int col_width;
extern int offset;
extern const char *format;

int help(int code) {
  printf(
    "%s: [FLAGS] FILENAME\n"
    "dump file as hex, oct or bin\n"
    "options:\n"
    "\t-c N\tcolumn count\n"
    "\t-w N\tcolumn width\n"
    "\t-o\toctal format\n"
    "\t-b\tbinary format\n"
    "\t-n\tno offset\n"
    "\t-A\tprint ASCII\n"
    "\t-h\tshow this help\n",
    pname
  );
  return code;
}

int printerr(int code, const char* msg) {
  if (!msg)
    msg = strerror(code);
  printf("%s: error: %s\n", pname, msg);
  return code;
}

void print_dump(char *buf) {
  static unsigned long row_count;
  if (offset)
    printf("%08x: ", row_count+=col_num);
  for (int i = 0; i < col_num; i++) {
    if (i && !(i % col_width))
      putchar(' ');
    printf(format, (unsigned char) buf[i]);
  }

  if (ascii) {
    printf("%2c ", '|');
    for (int i = 0; i < col_num; i++)
      printf("%c", (unsigned char) (isprint(buf[i]) && (buf[i] != '\n') ? buf[i] : ' '));
    printf("%2c", '|');
  }

  printf("\n");
}
