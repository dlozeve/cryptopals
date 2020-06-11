#include "io.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <key> <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *key = argv[1];
  const char *filename = argv[2];

  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening file %s\n", filename);
    return EXIT_FAILURE;
  }

  unsigned int key_length = strlen(key);

  char buf[1024];
  size_t nread = 0;
  size_t counter = 0;
  while ((nread = fread(buf, 1, sizeof buf, fp)) > 0) {
    for (size_t i = 0; i < nread; ++i) {
      printf("%02x", buf[i] ^ key[counter % key_length]);
      counter++;
    }
  }

  putchar('\n');

  if (fclose(fp)) {
    printf("Error closing file %s\n", filename);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
