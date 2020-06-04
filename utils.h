#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

unsigned char hex_to_byte(const char c);
size_t hex_to_bytes(unsigned char *out, const char hex[static 1]);
char *bytes_to_base64(char *out, const unsigned char in[static 1], size_t len);
double frequency_score(unsigned char *buf, size_t len);
unsigned int hamming(const char *s1, const char *s2);

#endif /* UTILS_H */
