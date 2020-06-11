#include "io.h"
#include <ctype.h>
#include <string.h>

unsigned char hex_to_byte(const char c) {
  if (isdigit(c)) {
    return c - '0';
  }
  return 10 + c - 'a';
}

size_t hex_to_bytes(unsigned char out[static 1], const char hex[static 1]) {
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

char *bytes_to_base64(char out[static 4], const unsigned char in[static 3],
                      size_t len) {
  for (size_t i = 0; i < len - 2; i += 3) {
    size_t j = i / 3 * 4;
    out[j] = base64_table[in[i] >> 2];
    out[j + 1] = base64_table[((in[i] & 0x03) << 4) | (in[i + 1] >> 4)];
    out[j + 2] = base64_table[((in[i + 1] & 0x0f) << 2) | (in[i + 2] >> 6)];
    out[j + 3] = base64_table[in[i + 2] & 0x3f];
  }
  return out;
}

size_t base64_to_bytes(unsigned char out[static 3], const char in[static 4]) {
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
