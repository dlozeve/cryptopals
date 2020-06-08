#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

unsigned char hex_to_byte(const char c);
size_t hex_to_bytes(unsigned char out[static 1], const char hex[static 1]);
char *bytes_to_base64(char out[static 4], const unsigned char in[static 3], size_t len);
size_t base64_to_bytes(unsigned char out[static 3], const char in[static 4]);
double frequency_score(size_t len, const char buf[static len]);
unsigned int hamming(const char s1[static 1], const char s2[static 1]);

#endif /* UTILS_H */
