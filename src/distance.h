#ifndef DISTANCE_H
#define DISTANCE_H

#include <string.h>

unsigned int hamming(size_t len, const unsigned char s1[static len],
                     const unsigned char s2[static len]);
double normalized_edit_distance(
    unsigned int block_size, unsigned int blocks_count,
    const unsigned char buf[static block_size * blocks_count]);

#endif /* DISTANCE_H */
