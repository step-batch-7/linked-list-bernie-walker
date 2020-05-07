#include "test.h"
#include "../list.h"

int is_list_empty(List_ptr list)
{
  return ((list->head == NULL) && (list->last == NULL)) ? 1 : 0;
}

void test_remove_all_occurrences(void)
{
  List_ptr list = create_list();
  add_unique(list, 1);
  add_unique(list, 2);
  add_unique(list, 3);
  insert_at(list, 1, 2);
  add_to_end(list, 1);
  assert_strict_equal("Should not remove non existing element from the list", remove_all_occurrences(list, 9), Failure);
  int isSuccess = remove_all_occurrences(list, 1) ^ Success;
  int doesHaveElement = has_element(list, 1) ^ Failure;
  assert_strict_equal("Should remove all the occurrences of an existing element", (isSuccess | doesHaveElement), Success);
  assert_strict_equal("Should update the head of the list when the first element is removed", list->head->value, 2);
  assert_strict_equal("Should update the last of the list when the last element is removed", list->last->value, 3);
  remove_all_occurrences(list, 2);
  remove_all_occurrences(list, 3);
  assert_strict_equal("Both head and last should be NULL after removal of an only element", is_list_empty(list), 1);
}

void test_remove_first_occurrence(void)
{
  List_ptr list = create_list();
  add_unique(list, 1);
  add_unique(list, 2);
  add_to_end(list, 1);
  assert_strict_equal("Should not remove non existing element", remove_first_occurrence(list, 3), Failure);
  assert_strict_equal("Should remove the first occurrence existing element", remove_first_occurrence(list, 1), Success);
  assert_strict_equal("Should update the count of the list", list->count, 2);
  assert_strict_equal("Should remove only the first occurrence", list->last->value, 1);
  assert_strict_equal("Should update the head when removed element was first element", list->head->value, 2);
  remove_first_occurrence(list, 1);
  assert_strict_equal("Should update the last when removed element was last element", list->last->value, 2);
  remove_first_occurrence(list, 2);
  assert_strict_equal("Both head and last should be NULL after removal of an only element", is_list_empty(list), 1);
}

void test_remove_from_end(void)
{
  List_ptr list = create_list();
  assert_strict_equal("Should not remove from an empty list", remove_from_end(list), Failure);
  add_unique(list, 1);
  add_unique(list, 2);
  assert_strict_equal("Should remove from the end of a non empty list", remove_from_end(list), Success);
  assert_strict_equal("Should update the last of the list", list->last->value, 1);
  assert_strict_equal("Should updated the count of the list", list->count, 1);
  remove_from_end(list);
  assert_strict_equal("Both head and last should be NULL after removal of an only element", is_list_empty(list), 1);
}

void test_remove_at(void)
{
  List_ptr list = create_list();
  assert_strict_equal("Should not remove from the list when a wrong position is given", remove_at(list, 2), Failure);
  add_unique(list, 1);
  add_unique(list, 2);
  add_unique(list, 3);
  assert_strict_equal("Should not remove from middle of the list", remove_at(list, 1), Success);
  assert_strict_equal("Should update the count of the list", list->count, 2);
  assert_strict_equal("Should not remove from the end of the list", remove_at(list, 1), Success);
  assert_strict_equal("Should not remove from starting of the list", remove_at(list, 0), Success);
  assert_strict_equal("Both head and last should be NULL after removal of an only element", is_list_empty(list), 1);
}

void test_remove_from_start(void)
{
  List_ptr list = create_list();
  assert_strict_equal("Should not remove from an empty list", remove_from_start(list), Failure);
  add_unique(list, 1);
  add_unique(list, 2);
  assert_strict_equal("Should remove from the start of a non empty list", remove_from_start(list), Success);
  assert_strict_equal("Should update the head of the list", list->head->value, 2);
  assert_strict_equal("Should updated the count of the list", list->count, 1);
  remove_from_start(list);
  assert_strict_equal("Both head and last should be NULL after removal of an only element", is_list_empty(list), 1);
}

void test_add_unique(void)
{
  List_ptr list = create_list();
  assert_strict_equal("Should add any element to an empty list", add_unique(list, 3), Success);
  assert_strict_equal("Should add a unique item to the list", add_unique(list, 2), Success);
  assert_strict_equal("The count of the list should be updated", list->count, 2);
  assert_strict_equal("Should not add a non unique item to the list", add_unique(list, 2), Failure);
  assert_strict_equal("Should add item at the end of the list", list->last->value, 2);
}

void test_insert_at(void)
{
  List_ptr list = create_list();
  assert_strict_equal("Should add at a valid postion", insert_at(list, 1, 0), Success);
  assert_strict_equal("Should add at at the starting of the list", list->head->value, 1);
  insert_at(list, 2, 1);
  assert_strict_equal("Should add at at the end of the list", list->last->value, 2);
  assert_strict_equal("The count of the list should be updated", list->count, 2);
  insert_at(list, 3, 1);
  assert_strict_equal("Should add in the middle of the list", list->head->next->value, 3);
  assert_strict_equal("Should not add at an invalid postion", insert_at(list, 6, 9), Failure);
}

void test_add_to_end(void)
{
  List_ptr list = create_list();
  assert_strict_equal("Element should be successfully added when memory is available", add_to_end(list, 8), Success);
  assert_strict_equal("Added element should be the value of the last", list->last->value, 8);
  assert_strict_equal("The count of the list should be updated", list->count, 1);
  assert_strict_equal("When the list is empty the added element should be the first element as well", list->last->value, 8);
  add_to_end(list, 6);
  assert_strict_equal("The element should be added to the ending of the list", list->last->value, 6);
}

void test_add_to_start(void)
{
  List_ptr list = create_list();
  assert_strict_equal("Element should be successfully added when memory is available", add_to_start(list, 9), Success);
  assert_strict_equal("Added element should be the value of the head", list->head->value, 9);
  assert_strict_equal("The count of the list should be updated", list->count, 1);
  assert_strict_equal("When the list is empty the added element should also be the last element", list->last->value, 9);
  add_to_start(list, 7);
  assert_strict_equal("The element should be added to the starting of the list", list->head->value, 7);
}

void test_has_element(void)
{
  List_ptr list = create_list();
  assert_strict_equal("Should not find the element which does not exist", has_element(list, 1), Failure);
  add_unique(list, 2);
  assert_strict_equal("Should find the element which exists", has_element(list, 2), Success);
}

int main(void)
{
  exec_test_suite("has_element", test_has_element);
  exec_test_suite("add_to_start", test_add_to_start);
  exec_test_suite("add_to_end", test_add_to_end);
  exec_test_suite("insert_at", test_insert_at);
  exec_test_suite("add_unique", test_add_unique);
  exec_test_suite("remove_from_start", test_remove_from_start);
  exec_test_suite("remove_at", test_remove_at);
  exec_test_suite("remove_from_end", test_remove_from_end);
  exec_test_suite("remove_first_occurrence", test_remove_first_occurrence);
  exec_test_suite("remove_all_occurrences", test_remove_all_occurrences);
  print_report();
  return 0;
}