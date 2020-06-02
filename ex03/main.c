#include "utils.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double frequency_score(unsigned char *buf, size_t len) {
  static const double english_freqs[26] = {
      0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, // A-G
      0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, // H-N
      0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, // O-U
      0.00978, 0.02360, 0.00150, 0.01974, 0.00074                    // V-Z
  };

  unsigned int counts[26] = {0};
  for (size_t i = 0; i < len; ++i) {
    unsigned char c = tolower(buf[i]) - 'a';
    if (c < 26) {
      counts[c]++;
    }
  }

  double chi2 = 0;
  for (size_t i = 0; i < 26; ++i) {
    double expected = len * english_freqs[i];
    chi2 += pow(counts[i] - expected, 2) / expected;
  }
  return chi2;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <hex1>\n", argv[0]);
    return EXIT_FAILURE;
  }

  unsigned char buf[512] = {0};
  size_t len = hex_to_bytes(buf, argv[1]);

  unsigned char cur[512];
  double min_score = INFINITY;
  unsigned char key;
  unsigned char best[512];
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
