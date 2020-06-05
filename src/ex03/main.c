#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <hex1>\n", argv[0]);
    return EXIT_FAILURE;
  }

  unsigned char buf[512] = {0};
  size_t len = hex_to_bytes(buf, argv[1]);

  char cur[512];
  double min_score = INFINITY;
  char key;
  char best[512];
  // Test for keys from A to z
  for (char c = 65; c < 127; ++c) {
    for (size_t i = 0; i < len; ++i) {
      cur[i] = buf[i] ^ c;
    }
    double score = frequency_score(cur, len);
    if (score < min_score) {
      min_score = score;
      key = c;
      memcpy(best, cur, len);
    }
  }
  for (size_t i = 0; i < len; ++i) {
    printf("%c", best[i]);
  }
  printf(" (key = %c, score = %.2f)\n", key, min_score);

  return EXIT_SUCCESS;
}
