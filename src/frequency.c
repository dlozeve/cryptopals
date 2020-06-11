#include "frequency.h"
#include <ctype.h>
#include <math.h>
#include <string.h>

double frequency_score(size_t len, const char buf[static len]) {
  static const double english_freqs[27] = {
      // A-Z
      0.0855, 0.0160, 0.0316, 0.0387, 0.01210, 0.0218, 0.0209, 0.0496, 0.0733,
      0.0022, 0.0081, 0.0421, 0.0253, 0.0717, 0.0747, 0.0207, 0.0010, 0.0633,
      0.0673, 0.0894, 0.0268, 0.0106, 0.0183, 0.0019, 0.0172, 0.0011,
      // space
      0.19182};

  // static const double english_freqs[27] = {
  //     // A-Z
  //     0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094,
  //     0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929,
  //     0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
  //     0.01974, 0.00074,
  //     // space
  //     0.19182};

  unsigned int counts[27] = {0};
  for (size_t i = 0; i < len; ++i) {
    if (!isprint(buf[i]) && buf[i] != '\n') {
      // If character is not printable, it's definitely not English.
      return INFINITY;
    }
    if (buf[i] == ' ') {
      counts[26]++;
      continue;
    }
    unsigned char c = tolower(buf[i]) - 'a';
    if (c < 26) {
      counts[c]++;
    }
  }

  double chi2 = 0;
  for (size_t i = 0; i < 27; ++i) {
    double expected = len * english_freqs[i];
    chi2 += pow(counts[i] - expected, 2) / expected;
  }
  return chi2;
}

char best_single_char_xor_key(size_t len, unsigned char buf[static len]) {
  char cur[len];
  double min_score = INFINITY;
  char key = 'X';

  for (char c = 32; c < 127; ++c) {
    for (size_t i = 0; i < len; ++i) {
      cur[i] = buf[i] ^ c;
    }
    double score = frequency_score(len, cur);
    if (score < min_score) {
      min_score = score;
      key = c;
    }
  }

  return key;
}
