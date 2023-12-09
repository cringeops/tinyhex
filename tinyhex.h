#define DEF_COL_WIDTH  4
#define DEF_COL_NUM    2
#define HEX_FORMAT     "%02x "
#define OCT_FORMAT     "%03o "
#define BIN_FORMAT     "%08b "

#define ARG_ASCII      'C'
#define ARG_BINARY     'b'
#define ARG_COL        'c'
#define ARG_HELP       'h'
#define ARG_OCTAL      'o'
#define ARG_OFFSET     'n'
#define ARG_WIDTH      'w'

int dump(const char *);
int help(int);
int printerr(int, const char *);
void print_dump(char *);
