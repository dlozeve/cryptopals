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

double normalized_edit_distance(
    unsigned int block_size, unsigned int blocks_count,
    const unsigned char buf[static block_size * blocks_count]) {
  double avg_dist = 0;
  for (size_t i = 0; i < blocks_count - 1; ++i) {
    avg_dist +=
        hamming(block_size, &buf[i * block_size], &buf[(i + 1) * block_size]);
  }

  return avg_dist / (double)block_size / ((double)blocks_count - 1.0);
}
