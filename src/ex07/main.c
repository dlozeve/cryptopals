#include "utils.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "mbedtls/aes.h"

#define BUF_SIZE 4096

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

  mbedtls_aes_context aes;

  if (fclose(fp)) {
    printf("Error closing file %s\n", filename);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
