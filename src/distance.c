#include <string.h>

unsigned int hamming(size_t len, const unsigned char s1[static len],
                     const unsigned char s2[static len]) {
  unsigned int res = 0;
  for (size_t i = 0; i < len; ++i) {
    unsigned int n = s1[i] ^ s2[i];
    while (n) {
      res += n & 1;
      n >>= 1;
    }
  }
  return res;
}
