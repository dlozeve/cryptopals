#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"
#include <stdlib.h>
#include "utils.h"

static MunitResult test_hex_to_byte(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  assert_uchar(hex_to_byte('0'), ==, 0);
  assert_uchar(hex_to_byte('a'), ==, 10);
  assert_uchar(hex_to_byte('f'), ==, 15);

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    {"/hex_to_byte", test_hex_to_byte, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite test_suite = {
  (char*) "",
  test_suite_tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};
  
int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
