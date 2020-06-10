#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"
#include "utils.h"
#include <math.h>
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

static MunitResult test_base64_decode(const MunitParameter params[],
                                      void *data) {
  (void)params;
  (void)data;

  const char *input = "TWFu";
  unsigned char buf[512] = {0};
  size_t len = base64_to_bytes(buf, input);
  assert_string_equal((char *)buf, "Man");
  assert_size(len, ==, 3);

  const char *input2 = "WUVMTE9XIFNVQk1BUklORQ==";
  memset(buf, 0, 512);
  len = base64_to_bytes(buf, input2);
  assert_string_equal((char *)buf, "YELLOW SUBMARINE");
  assert_size(len, ==, 18); // the 2 = create two bytes of padding at the end

  return MUNIT_OK;
}

static MunitResult test_frequency_score(const MunitParameter params[],
                                        void *data) {
  (void)params;
  (void)data;

  // Non-printable characters should return INFINITY.
  assert(isfinite(frequency_score(16, "YELLOW SUBMARINE")));
  assert(isinf(frequency_score(1, "\0x07")));
  assert(isinf(frequency_score(17, "YELLOW\0x07 SUBMARINE")));

  // Teh frequency score should be case-insensitive.
  assert_double_equal(frequency_score(16, "YELLOW SUBMARINE"),
                      frequency_score(16, "yellow submarine"), 12);

  // E is more frequent than Z.
  assert_double(frequency_score(3, "eee"), <, frequency_score(3, "zzz"));
  // Space is more frequent than anything.
  assert_double(frequency_score(3, "   "), <, frequency_score(3, "eee"));

  return MUNIT_OK;
}

static MunitResult test_hamming(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  assert_int(hamming(14, (const unsigned char *)"this is a test",
                     (const unsigned char *)"wokka wokka!!!"),
             ==, 37);

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    {"/hex_to_byte", test_hex_to_byte, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/hex_to_base64", test_hex_to_base64, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/base64_decode", test_base64_decode, NULL, NULL, MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/frequency_score", test_frequency_score, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {"/hamming", test_hamming, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite test_suite = {(char *)"", test_suite_tests, NULL, 1,
                                      MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
