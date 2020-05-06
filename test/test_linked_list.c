#include "test.h"
#include "../list.h"

void test_add_to_end(void)
{
  List_ptr list = create_list();
  assert_strict_equal("Element should be successfully added when memory is available", add_to_end(list, 8), Success);
  assert_strict_equal("Added element should be the value of the last", list->last->value, 8);
  assert_strict_equal("When the list is empty the added element should be the first element as well", list->last->value, 8);
  add_to_end(list, 6);
  assert_strict_equal("The element should be added to the ending of the list", list->last->value, 6);
}

void test_add_to_start(void)
{
  List_ptr list = create_list();
  assert_strict_equal("Element should be successfully added when memory is available", add_to_start(list, 9), Success);
  assert_strict_equal("Added element should be the value of the head", list->head->value, 9);
  assert_strict_equal("When the list is empty the added element should also be the last element", list->last->value, 9);
  add_to_start(list, 7);
  assert_strict_equal("The element should be added to the starting of the list", list->head->value, 7);
}

int main(void)
{
  exec_test_suite("add_to_start", test_add_to_start);
  exec_test_suite("add_to_end", test_add_to_end);
  return 0;
}