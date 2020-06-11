#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <string.h>

double frequency_score(size_t len, const char buf[static len]);
char best_single_char_xor_key(size_t len, unsigned char buf[static len]);

#endif /* FREQUENCY_H */
