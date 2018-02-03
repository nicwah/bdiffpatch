#include <stdio.h>
#include <stdbool.h>

int bdiff(const char* s, char* t, char* diff, unsigned short len) {
  printf("bdiff\n");
  unsigned short p_offset, p_len;
  int p_len = 0;
  int p_idx = 0;
  int res = 0;

  for (unsigned short i; i<len; i++) {
    if (s[i] == t[i]) {
      if (p_len>0) {
	//terminate patch
	*((unsigned_short*)&diff[p_idx]) = p_len;
	p_index += p_len+4;
	p_len = 0;
      }
    } else {
      if (p_len>0) {
	p_len++;
	diff[p_index+4+p_len] = t[i];
      } else {
	// start patch
	diff[p_index] = i;
      }
    }
  }
}

int bpatch(char* s, char* t, char* diff, int len) {
  printf("bpatch\n");
}
