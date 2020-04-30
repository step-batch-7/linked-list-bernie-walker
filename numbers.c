#include <stdio.h>
#include "list.h"

#define MENU "Main Menu\n---------\n\
(m) exit\n\nPlease enter the alphabet of the operation you would like to perform\n\n"
// (a) add a number to the end of the list\n\
// (b) add a number to the start of the list\n\
// (c) insert a number at a given position in the list\n\
// (d) add a unique item on the list at the end\n\
// (e) remove a number from the beginning of the list\n\
// (f) remove a number from the end of the list\n\
// (g) remove a number from a given position in the list\n\
// (h) remove first occurrence of a number\n\
// (i) remove all occurrences of a number\n\
// (j) clear the whole list\n\
// (k) check if a number exists in the list\n\
// (l) display the list of numbers\n\

char get_user_option(void);

char get_user_option(void)
{
  printf("%s", MENU);
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
    printf("operation happened\n\n");
    user_option = get_user_option();
  }

  printf("Exiting...\n");

  return 0;
}