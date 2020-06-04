#include "utils.h"
#include <ctype.h>
#include <math.h>
#include <string.h>

#define min(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _b : _a;                                                         \
  })

#define max(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _a : _b;                                                         \
  })

unsigned char hex_to_byte(const char c) {
  if (isdigit(c)) {
    return c - '0';
  }
  return 10 + c - 'a';
}

size_t hex_to_bytes(unsigned char *out, const char hex[static 1]) {
  for (size_t i = 0; i < strlen(hex); ++i) {
    char c = tolower(hex[i]);
    unsigned char value = hex_to_byte(c);
    if (i % 2 == 0) {
      value <<= 4;
    }
    out[i / 2] += value;
  }
  return strlen(hex) / 2 + strlen(hex) % 2;
}

static const char base64_table[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *bytes_to_base64(char *out, const unsigned char in[static 1], size_t len) {
  for (size_t i = 0; i < len - 2; i += 3) {
    size_t j = i / 3 * 4;
    out[j] = base64_table[in[i] >> 2];
    out[j + 1] = base64_table[((in[i] & 0x03) << 4) | (in[i + 1] >> 4)];
    out[j + 2] = base64_table[((in[i + 1] & 0x0f) << 2) | (in[i + 2] >> 6)];
    out[j + 3] = base64_table[in[i + 2] & 0x3f];
  }
  return out;
}

size_t base64_to_bytes(unsigned char *out, const char *in) {
  char decoding_table[256] = {0};
  for (size_t i = 0; i < 64; ++i) {
    decoding_table[(unsigned char)base64_table[i]] = i;
  }

  size_t in_length = strlen(in);
  if (in_length % 4 != 0) {
    return 0;
  }

  size_t i = 0;
  for (size_t j = 0; j < in_length - 3;) {
    unsigned char sextet1 =
        in[j] == '=' ? 0 : decoding_table[(unsigned char)in[j]];
    unsigned char sextet2 =
        in[j + 1] == '=' ? 0 : decoding_table[(unsigned char)in[j + 1]];
    unsigned char sextet3 =
        in[j + 2] == '=' ? 0 : decoding_table[(unsigned char)in[j + 2]];
    unsigned char sextet4 =
        in[j + 3] == '=' ? 0 : decoding_table[(unsigned char)in[j + 3]];

    out[i] = sextet1 << 2;
    out[i] += sextet2 >> 4;
    out[i + 1] = sextet2 << 4;
    out[i + 1] += sextet3 >> 2;
    out[i + 2] = sextet3 << 6;
    out[i + 2] += sextet4;

    j += 4;
    i += 3;
  }

  return i;
}

double frequency_score(const char *buf, size_t len) {
  static const double english_freqs[27] = {
      0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, // A-G
      0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, // H-N
      0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, // O-U
      0.00978, 0.02360, 0.00150, 0.01974, 0.00074,                   // V-Z
      0.19182                                                        // space
  };

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

unsigned int hamming(const char *s1, const char *s2) {
  unsigned int len1 = strlen(s1);
  unsigned int len2 = strlen(s2);

  unsigned int res = 0;
  for (size_t i = 0; i < min(len1, len2); ++i) {
    unsigned int n = s1[i] ^ s2[i];
    while (n) {
      res += n & 1;
      n >>= 1;
    }
  }
  return res;
}
