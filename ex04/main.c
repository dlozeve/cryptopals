#include "utils.h"
#include <ctype.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("Error opening file %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  printf("line | key | score | cleartext\n");
  printf("-----+-----+-------+-------------------------------\n");

  unsigned int line_count = 0;
  char *line = NULL;
  size_t line_length = 0;
  ssize_t nread = 0;
  size_t len;

  while ((nread = getline(&line, &line_length, fp)) != -1) {
    line_count++;

    line[60] = '\0';
    // printf("%3u: %s\n", line_count, line);
    unsigned char buf[512] = {0};
    len = hex_to_bytes(buf, line);

    char cur[512] = {'\0'};
    for (char c = 32; c < 127; ++c) {
      for (size_t i = 0; i < len; ++i) {
        cur[i] = buf[i] ^ c;
      }
      double score = frequency_score(cur, len);
      if (score < 40.0) {
        printf("%4u | %c   | %5.1f | ", line_count, c,
               score);
        for (size_t i = 0; i < len; ++i) {
	  if (isprint(cur[i])) {
	    putchar(cur[i]);
	  } else if (cur[i] == '\n') {
	    printf("\\n");
	  }
        }
	printf("\n");
      }
    }
  }

  free(line);

  if (fclose(fp)) {
    printf("Error closing file %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
