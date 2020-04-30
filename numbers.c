#include <stdio.h>
#include "list.h"

#define MENU "Main Menu\n---------\n\
(a) add a number to the end of the list\n\
(b) add a number to the start of the list\n\
(c) insert a number at a given position in the list\n\
(d) add a unique item on the list at the end (NOTE: item will not be added if it is same as the last element)\n\
(e) remove a number from the beginning of the list\n\
(j) clear the whole list\n\
(l) display the list of numbers\n\
(m) exit\n\nPlease enter the alphabet of the operation you would like to perform\n"
// (f) remove a number from the end of the list\n\
// (g) remove a number from a given position in the list\n\
// (h) remove first occurrence of a number\n\
// (i) remove all occurrences of a number\n\
// (k) check if a number exists in the list\n\

#define FAILED printf("Operation Not Successful wrong input or memory exhausted\n")
#define WRONG_OP printf("Invalid Option\n")

int get_user_in(char[]);
void add_element_at(List_ptr);
void remove_element(List_ptr, Status (*)());
void push_element(List_ptr, Status (*)());
void perform_operation(List_ptr, char);
char get_user_option(void);

int get_user_in(char message[])
{
  int user_in;
  printf("%s\n", message);
  scanf("%d", &user_in);
  return user_in;
}

void add_element_at(List_ptr list)
{
  int value = get_user_in("Please enter the element you want to add");
  int position = get_user_in("Please enter the position you want to add the element at");
  Status stat = insert_at(list, value, position);

  if (stat != 0)
  {
    FAILED;
    return;
  }

  printf("Element successfully added\n");
}

void remove_element(List_ptr list, Status (*remover)(List_ptr))
{
  Status stat = remover(list);

  if (stat != 0)
  {
    FAILED;
    return;
  }

  printf("Element successfully removed\n");
}

void add_element(List_ptr list, Status (*adder)(List_ptr, int))
{
  int element = get_user_in("Please enter the element to add");
  Status stat = adder(list, element);

  if (stat != 0)
  {
    FAILED;
    return;
  }

  printf("Element successfully added\n");
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

  case 'j':
    clear_list(list);
    printf("List Cleared\n");
    break;

  case 'l':
    display(list);
    break;

  default:
    WRONG_OP;
    break;
  }
}

char get_user_option(void)
{
  NEW_LINE;
  printf("%s", MENU);
  NEW_LINE;
  fflush(stdin);
  return getchar();
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