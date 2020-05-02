#include <stdio.h>
#include "list.h"

void print_menu(void);
void print_success(char[]);
void print_failure(char[]);
void print_status(Status, char[], char[]);
int get_user_in(char[]);
void check_if_present(List_ptr);
void remove_occurrences(List_ptr, Status (*)());
void remove_element_from(List_ptr);
void add_element_at(List_ptr);
void remove_element(List_ptr, Status (*)());
void push_element(List_ptr, Status (*)());
void perform_operation(List_ptr, char);
char get_user_option(void);

void print_menu(void)
{
  NEW_LINE;
  printf("Main Menu\n---------\n");
  printf("(a) add a number to the end of the list\n");
  printf("(b) add a number to the start of the list\n");
  printf("(c) insert a number at a given position in the list\n");
  printf("(d) add a unique item on the list at the end (NOTE: item will not be added if it is same as the last element)\n");
  printf("(e) remove a number from the beginning of the list\n");
  printf("(f) remove a number from the end of the list\n");
  printf("(g) remove a number from a given position in the list\n");
  printf("(h) remove first occurrence of a number\n");
  printf("(i) remove all occurrences of a number\n");
  printf("(j) clear the whole list\n");
  printf("(k) check if a number exists in the list\n");
  printf("(l) display the list of numbers\n");
  printf("(m) exit\n\nPlease enter the alphabet of the operation you would like to perform\n");
  NEW_LINE;
}

void print_success(char action[])
{
  printf("Element successfully %s\n", action);
}

void print_failure(char action[])
{
  printf("Could not %s element. Wrong input or memory exhausted\n", action);
}

void print_status(Status stat, char on_success[], char on_failure[])
{
  if (stat != 0)
  {
    print_failure(on_failure);
    return;
  }
  print_success(on_success);
}

int get_user_in(char message[])
{
  int user_in;
  printf("%s\n", message);
  fflush(stdin);
  scanf("%d", &user_in);
  return user_in;
}

void check_if_present(List_ptr list)
{
  int number = get_user_in("Please enter the number you want to find");
  Status stat = has_element(list, number);

  if (stat != 0)
  {
    printf("Element is not present in the list\n");
    return;
  }

  printf("Element is present in the list\n");
}

void remove_occurrences(List_ptr list, Status (*remover)(List_ptr, int))
{
  int number = get_user_in("Please enter the number you want to remove");
  Status stat = remover(list, number);
  print_status(stat, "removed", "remove");
}

void remove_element_from(List_ptr list)
{
  int position = get_user_in("Please enter the position you want to remove the element from");
  Status stat = remove_at(list, position);
  print_status(stat, "removed", "remove");
}

void add_element_at(List_ptr list)
{
  int value = get_user_in("Please enter the element you want to add");
  int position = get_user_in("Please enter the position you want to add the element at");
  Status stat = insert_at(list, value, position);
  print_status(stat, "added", "add");
}

void remove_element(List_ptr list, Status (*remover)(List_ptr))
{
  Status stat = remover(list);
  print_status(stat, "removed", "remove");
}

void add_element(List_ptr list, Status (*adder)(List_ptr, int))
{
  int element = get_user_in("Please enter the element to add");
  Status stat = adder(list, element);
  print_status(stat, "added", "add");
}

void perform_operation(List_ptr list, char opcode)
{
  switch (opcode)
  {
  case 'a':
    add_element(list, add_to_end);
    break;

  case 'b':
    add_element(list, add_to_start);
    break;

  case 'c':
    add_element_at(list);
    break;

  case 'd':
    add_element(list, add_unique);
    break;

  case 'e':
    remove_element(list, remove_from_start);
    break;

  case 'f':
    remove_element(list, remove_from_end);
    break;

  case 'g':
    remove_element_from(list);
    break;

  case 'h':
    remove_occurrences(list, remove_first_occurrence);
    break;

  case 'i':
    remove_occurrences(list, remove_all_occurrences);
    break;

  case 'j':
    clear_list(list);
    printf("List Cleared\n");
    break;

  case 'k':
    check_if_present(list);
    break;

  case 'l':
    display(list);
    break;

  default:
    printf("Invalid Option\n");
    break;
  }
}

char get_user_option(void)
{
  char option, terminator;
  print_menu();
  fflush(stdin);
  scanf("%c%c", &option, &terminator);
  return terminator == '\n' ? option : '\0';
}

int main(void)
{
  List_ptr user_list = create_list();
  char user_option = get_user_option();

  while (user_option != 'm')
  {
    system("clear");
    perform_operation(user_list, user_option);
    user_option = get_user_option();
  }

  destroy_list(user_list);
  printf("Exiting...");
  NEW_LINE;

  return 0;
}