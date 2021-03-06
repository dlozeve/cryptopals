#include "distance.h"
#include "frequency.h"
#include "io.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 4096

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
  int c;
  size_t nread = 0;
  while ((c = fgetc(fp)) != EOF) {
    if (c == '\n' || c == '\r') { // ignore newlines
      continue;
    }
    input[nread] = c;
    nread++;
  }
  if (nread == 0) {
    printf("Cannot read any character from file %s\n", filename);
    return EXIT_FAILURE;
  }

  if (fclose(fp)) {
    printf("Error closing file %s\n", filename);
    return EXIT_FAILURE;
  }

  unsigned char buf[BUF_SIZE] = {0};
  size_t len = base64_to_bytes(buf, input);
  if (len == 0) {
    printf("Could not decode base64\n");
    return EXIT_FAILURE;
  }

  unsigned int keysize = 0;
  double min_edit_dist = INFINITY;
  for (unsigned int i = 2; i < 40; ++i) {
    double edit_dist = normalized_edit_distance(i, len / i, buf);
    if (edit_dist < min_edit_dist) {
      min_edit_dist = edit_dist;
      keysize = i;
    }
  }

  printf("keysize = %u, min edit distance = %f\n", keysize, min_edit_dist);

  size_t blocks_count = 1 + len / keysize;
  unsigned char blocks[keysize][blocks_count];
  memset(blocks, 0, blocks_count * keysize);

  for (size_t i = 0; i < blocks_count; ++i) {
    for (size_t j = 0; j < keysize; ++j) {
      blocks[j][i] = buf[i * keysize + j];
    }
  }

  char key[keysize];
  for (size_t j = 0; j < keysize; ++j) {
    key[j] = best_single_char_xor_key(blocks_count, blocks[j]);
  }
  printf("Key: %s\n\n", key);

  for (size_t i = 0; i < len; ++i) {
    printf("%c", buf[i] ^ key[i % keysize]);
  }
  putchar('\n');

  return EXIT_SUCCESS;
}
