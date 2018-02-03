#include "bdiffpatch.h"

int bdiff(const char* s, const char* t, char* diff, const unsigned short len) {
  unsigned short p_idx = 0;
  unsigned short p_len = 0;

  for (unsigned short i=0; i<len; i++) {
    if (s[i] == t[i]) {
      if (p_len>0) {
	//terminate patch region
	*((unsigned short*)&diff[p_idx+2]) = p_len;
	p_idx += p_len+4;
	p_len = 0;
      }
    } else {
      if (p_idx+4+p_len >= len)
	return -1; // overflow

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

  // write patch region of 0 length as end marker if space
  if (p_idx+4<=len) {
     *((unsigned short*)&diff[p_idx+2]) = 0;
  }

  return p_idx;
}

void bpatch(char* s, const char* diff, const unsigned short len) {
  unsigned short p_offset = 0;
  unsigned short p_len    = 0;
  unsigned short p_idx    = 0;

  for (unsigned short i=0; i<len;) {
    if (p_idx == p_len) {
      // Patch region start
      p_offset = *((unsigned short*)&diff[i]);
      p_len = *((unsigned short*)&diff[i+2]);
      p_idx = 0;
      if (p_len == 0) 
	break; // no more patch regions
      i+=4;
    } else {
      s[p_offset+p_idx] = diff[i];
      p_idx++;
      i++;
    }
  }
}
