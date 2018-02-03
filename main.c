#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bdiffpatch.h"

void pbuf(const char* b, const unsigned short len) {
  printf("\n");
  for(unsigned short i=0; i<len; i++) {
    printf("%c", b[i]);
  }
}

void bcheck(const char* b1, const char* b2, const unsigned short len) {
  for(unsigned short i=0; i<len; i++) {
    if (b1[i] != b2[i]) {
      printf("\nNot equal!\n");
      return;
    }
  }
  printf("\nEqual!\n");
}

void ppatch(const char* diff, const unsigned short len) {
  unsigned short p_offset = 0;
  unsigned short p_len = 0;

  for (unsigned short i=0; i<len;) {
    if (p_len == 0) {
      // Patch region start
      p_offset = *((unsigned short*)&diff[i]);
      p_len = *((unsigned short*)&diff[i+2]);
      if (p_len == 0) 
	break; // no more patch regions
      printf("\npatch offset:%i, length=%i data:", p_offset, p_len);
      i+=4;
    } else {
      printf("%c",diff[i]);
      p_len--;
      i++;
    }
  }
  printf("\n");
}

void test(const char* s_in, const char* t) {
  char *d, *s;
  int res = 0;
  int len = strlen(s_in);

  s=strdup(s_in);
  d=strdup(s);

  printf("************* TEST STARTED *************");
  printf("source: ");
  pbuf(s, len);

  printf("\n");
  printf("target: ");
  pbuf(t, len);

  res = bdiff(s, t, d, len);
  
  printf("\n");
  printf("bdiff() result %i\n", res);
  
  if (res < 0) {
    printf("Patch not computed!\n");
    return;
  }

  ppatch(d, len);
  
  bpatch(s, d, len);

  printf("patched source: ");
  pbuf(s, len);

  bcheck(s, t, len);

  free(d);
}

void main(int argc, char** argv) {
  char s1[] = "abcdefghijklmnopqrstuvxyz";
  char s2[] = "abpatch1ijklmnopatch2vxyz";
  char s3[] = "9999999999999999999999999";
  char s3x[] = "999999999999999999999vxyz";
  char s3y[] = "abcd999999999999999999999";
  char s4[] = "abcde";
  char s5[] = "abcdf";
  char s6[] = "xbcde";
  char s7[] = "abcd";  
  char s8[] = "a";
  char s9[] = "b";

  printf("Hello!\n");

  test(s1, s2);
  test(s1, s1);
  test(s1, s3);
  test(s1, s3x);
  test(s1, s3y);
  test(s4, s5);
  test(s4, s6);
  test(s7, s7);
  test(s8, s9);

  printf("\nGoodbye!\n");
}
