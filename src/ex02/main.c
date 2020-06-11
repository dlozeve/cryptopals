#include "io.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <hex1> <hex2>\n", argv[0]);
    return EXIT_FAILURE;
  }

  unsigned char buf1[512] = {0};
  size_t len1 = hex_to_bytes(buf1, argv[1]);
  unsigned char buf2[512] = {0};
  size_t len2 = hex_to_bytes(buf2, argv[2]);

  if (len1 != len2) {
    printf("Different lengths!\n");
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < len1; ++i) {
    unsigned char c = buf2[i] ^ buf1[i];
    printf("%x", c);
  }
  printf("\n");

  return EXIT_SUCCESS;
}
