#include "utils.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 4096

double normalized_edit_distance(const unsigned char *buf,
                                unsigned int keysize) {
  char block1[keysize];
  char block2[keysize];
  char block3[keysize];
  char block4[keysize];

  for (size_t i = 0; i < keysize; ++i) {
    block1[i] = buf[i];
    block2[i] = buf[keysize + i];
    block3[i] = buf[2 * keysize + i];
    block4[i] = buf[3 * keysize + i];
  }

  double dist1 = hamming(block1, block2) / (double)keysize;
  double dist2 = hamming(block2, block3) / (double)keysize;
  double dist3 = hamming(block3, block4) / (double)keysize;

  return (dist1 + dist2 + dist3) / 3;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *filename = argv[1];

  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening file %s\n", filename);
    return EXIT_FAILURE;
  }

  char input[BUF_SIZE] = {'\0'};
  size_t nread = fread(input, 1, BUF_SIZE, fp);
  if (nread == 0) {
    printf("Cannot read any character from file %s\n", filename);
    return EXIT_FAILURE;
  }

  unsigned char buf[BUF_SIZE] = {0};
  size_t len = base64_to_bytes(buf, input);
  if (len == 0) {
    printf("Could not decode base64\n");
    return EXIT_FAILURE;
  }

  unsigned int keysize = 40;
  double min_edit_dist = INFINITY;
  for (unsigned int i = 40; i > 1; --i) {
    double edit_dist = normalized_edit_distance(buf, i);
    if (edit_dist < min_edit_dist) {
      min_edit_dist = edit_dist;
      keysize = i;
    }
  }

  printf("keysize = %u, min edit distance = %f\n", keysize, min_edit_dist);

  if (fclose(fp)) {
    printf("Error closing file %s\n", filename);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}