#include "test.h"

void print_description(char description[])
{
  printf("\n\033[1m%s\033[0m\n\n", description);
}

void show_test_values(int actual, int expected)
{
  printf("\n\t\033[32mExpected: %d\033[0m\t\033[91mActual: %d\033[0m\n\n", actual, expected);
}

void print_test_status(char assertion_message[], Test_status status)
{
  char *mark = status == Passed ? "\033[32m✓\033[0m\033[1;30m" : "\033[31m✗";
  printf("    %s %s\n\033[0m", mark, assertion_message);
}

void assert_strict_equal(char message[], int actual, int expected)
{
  if (actual == expected)
  {
    print_test_status(message, Passed);
    return;
  }

  print_test_status(message, Failed);
  show_test_values(actual, expected);
}

void exec_test_suite(char description[], void (*test_suite)(void))
{
  print_description(description);
  test_suite();
}