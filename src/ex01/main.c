#include "io.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[argc + 1]) {
  if (argc < 2) {
    printf("Usage: %s <hex>\n", argv[0]);
    return EXIT_FAILURE;
  }

  unsigned char buf[512] = {0};
  size_t len = hex_to_bytes(buf, argv[1]);
  char out[512] = {'\0'};
  bytes_to_base64(out, buf, len);
  printf("%s\n", out);

  return EXIT_SUCCESS;
}
