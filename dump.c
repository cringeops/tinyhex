#include "tinyhex.h"

extern int col_num;

int dump(const char *fname) {
  FILE *fp = fopen(fname, "r");
  if (fp == NULL)
    return printerr(errno, 0);

  char buf[DEF_BUF_SIZE] = {0};
	setvbuf(stdout, 0, _IOFBF, 0);

	int chunk_sz = DEF_BUF_SIZE, pos = 0;
	while (!feof(fp)) {
		chunk_sz=DEF_BUF_SIZE;
    fread(buf, chunk_sz, 1, fp);
    print_dump(buf);
	}

  fclose(fp);
  return 0;
}
