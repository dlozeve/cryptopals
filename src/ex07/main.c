#include "mbedtls/aes.h"
#include "utils.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

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
  mbedtls_aes_init(&aes);
  int err =
      mbedtls_aes_setkey_dec(&aes, (const unsigned char *)key, strlen(key) * 8);
  if (err) {
    printf("Key should be 16, 24, or 32 bytes long\n");
    return EXIT_FAILURE;
  }

  unsigned char output[BUF_SIZE] = {0};
  err = mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, buf, output);
  if (err) {
    printf("Could not decode buffer\n");
    return EXIT_FAILURE;
  }

  if (fclose(fp)) {
    printf("Error closing file %s\n", filename);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
