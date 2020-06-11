#ifndef IO_H
#define IO_H

#include <stdlib.h>

unsigned char hex_to_byte(const char c);
size_t hex_to_bytes(unsigned char out[static 1], const char hex[static 1]);
char *bytes_to_base64(char out[static 4], const unsigned char in[static 3],
                      size_t len);
size_t base64_to_bytes(unsigned char out[static 3], const char in[static 4]);

#endif /* IO_H */
