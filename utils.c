#include "utils.h"
#include <ctype.h>
#include <string.h>

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

unsigned char *bytes_to_base64(unsigned char *out,
                               const unsigned char in[static 1], size_t len) {
  static const unsigned char base64_table[65] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  for (size_t i = 0; i < len - 2; i += 3) {
    size_t j = i / 3 * 4;
    out[j] = base64_table[in[i] >> 2];
    out[j + 1] = base64_table[((in[i] & 0x03) << 4) | (in[i + 1] >> 4)];
    out[j + 2] = base64_table[((in[i + 1] & 0x0f) << 2) | (in[i + 2] >> 6)];
    out[j + 3] = base64_table[in[i + 2] & 0x3f];
  }
  return out;
}
