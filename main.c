#include <stdio.h>
#include <string.h>
#include "bdiffpatch.h"

void main(int argc, char** argv) {
  char s[] = "abcdefghijklmnopqrstuvxyz";
  char t[] = "abpatch1ghijklmnopatch2yz";
  char d[] = "abcdefghijklmnopqrstuvxyz";
  char r[] = "                         ";
  int len = strlen(s);
  int res = 0;

  printf("Hello\n");
  res = bdiff(s, t, d, len);
  
  res = bpatch(s, t, r, len);

  printf("Goodbye!\n");
}
