#ifndef DISTANCE_H
#define DISTANCE_H

#include <string.h>

unsigned int hamming(size_t len, const unsigned char s1[static len],
                     const unsigned char s2[static len]);

#endif /* DISTANCE_H */
