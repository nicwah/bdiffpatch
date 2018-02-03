#include <stdio.h>
#include <stdbool.h>

int bdiff(const char* s, char* t, char* diff, unsigned short len) {
  printf("bdiff\n");
  unsigned short p_idx, p_len = 0;

  for (unsigned short i; i<len; i++) {
    if (s[i] == t[i]) {
      if (p_len>0) {
	//terminate patch region
	*((unsigned short*)&diff[p_idx+2]) = p_len;
	p_idx += p_len+4;
	p_len = 0;
      }
    } else {
      if (p_len == 0) {
	// start patch region
	*((unsigned short*)&diff[p_idx]) = i;
      }
      diff[p_idx+4+p_len] = t[i];
      p_len++;
    }
  }

  if (p_len>0) {
    //terminate patch
    *((unsigned short*)&diff[p_idx+2]) = p_len;
    p_idx += p_len+4;
    p_len = 0;
  }

  return p_idx;
}

int bpatch(char* s, char* t, char* diff, int len) {
  printf("bpatch\n");
}
