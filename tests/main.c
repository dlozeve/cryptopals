#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"
#include "utils.h"
#include <stdlib.h>

static MunitResult test_hex_to_byte(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  assert_uchar(hex_to_byte('0'), ==, 0);
  assert_uchar(hex_to_byte('a'), ==, 10);
  assert_uchar(hex_to_byte('f'), ==, 15);

  return MUNIT_OK;
}

static MunitResult test_hex_to_base64(const MunitParameter params[],
                                      void *data) {
  (void)params;
  (void)data;
  const char *input = "49276d206b696c6c696e6720796f757220627261696e206c696b6520"
                      "6120706f69736f6e6f7573206d757368726f6f6d";

  unsigned char buf[512] = {0};
  size_t len = hex_to_bytes(buf, input);

  assert_size(len, ==, 48);

  char out[512] = {'\0'};
  bytes_to_base64(out, buf, len);

  assert_size(strlen(out), ==, 64);
  assert_string_equal(
      out, "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    {"/hex_to_byte", test_hex_to_byte, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/hex_to_base64", test_hex_to_base64, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite test_suite = {(char *)"", test_suite_tests, NULL, 1,
                                      MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
