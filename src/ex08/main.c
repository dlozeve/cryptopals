#include "utils.h"
#include <stdio.h>

#define BUF_SIZE 1024

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

  char *line = NULL;
  size_t line_length = 0;
  ssize_t nread = 0;
  while ((nread = getline(&line, &line_length, fp)) != -1) {
    line[nread - 1] = '\0'; /* Remove the newline character */
    unsigned char buf[BUF_SIZE] = {0};
    size_t len = hex_to_bytes(buf, line);
  }
  free(line);

  if (fclose(fp)) {
    printf("Error closing file %s\n", filename);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
