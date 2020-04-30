#include <stdio.h>
#include <stdlib.h>

#ifndef __LIST_H
#define __LIST_H
#define NEW_LINE printf("\n");

typedef enum
{
  Success,
  Failure
} Status;

typedef struct node
{
  int value;
  struct node *next;
} Node;

typedef Node *Node_ptr;

typedef struct
{
  Node *head;
  Node *last;
  size_t count;
} List;

typedef List *List_ptr;

Node_ptr create_node(int);
List_ptr create_list(void);
Node_ptr get_nth_node(List_ptr, int);

void display(List_ptr);

Status add_to_end(List_ptr, int);
Status add_to_start(List_ptr, int);
Status insert_at(List_ptr, int, int);
Status add_unique(List_ptr, int);

Status remove_from_start(List_ptr);
Status remove_at(List_ptr, int);
Status remove_from_end(List_ptr);

Status remove_first_occurrence(List_ptr, int value);
Status remove_all_occurrences(List_ptr, int value);

Status clear_list(List_ptr); // Removes all elements in the list
void destroy_list(List_ptr); // Frees the elements and the list structure from memory

#endif