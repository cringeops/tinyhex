# tinyhex
a tiny hexadecimal, octal and binary dump utility written in C.

## Build
```
gcc tinyhex.c -O2 -march=native -o tinyhex
```

## Usage
```
tinyhex: [FLAGS] FILENAME
options:
-c N column count
-w N column width
-o octal format
-b binary format
-n no offset
-A print ASCII
-h show this help
```
