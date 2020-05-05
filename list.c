#include "list.h"

Node_ptr create_node(int value)
{
  Node *new_node = malloc(sizeof(Node));

  if (new_node == NULL)
  {
    return new_node;
  }

  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

List_ptr create_list(void)
{
  List *new_list = malloc(sizeof(List));
  new_list->head = NULL;
  new_list->last = NULL;
  new_list->count = 0;
  return new_list;
}

Node_ptr get_nth_node(List_ptr list, int position)
{
  Node_ptr walker = list->head;
  int index = 0;

  if ((position >= list->count) || (position < 0))
  {
    return NULL;
  }

  while ((walker != NULL) && (index != position))
  {
    walker = walker->next;
    ++index;
  }

  return walker;
}

void display(List_ptr list)
{
  Node_ptr walker = list->head;

  printf("Contents are ==> ");
  while (walker != NULL)
  {
    printf("%d ", walker->value);
    walker = walker->next;
  }

  NEW_LINE;
}

Status has_element(List_ptr list, int number)
{
  Node_ptr walker = list->head;
  while (walker != NULL)
  {
    if (walker->value == number)
    {
      return Success;
    }
    walker = walker->next;
  }

  return Failure;
}

Status add_to_start(List_ptr list, int value)
{
  Node_ptr new_node = create_node(value);

  if (new_node == NULL)
  {
    return Failure;
  }

  new_node->next = list->head;
  list->head = new_node;
  ++list->count;

  if (list->last == NULL)
  {
    list->last = list->head;
  }

  return Success;
}

Status add_to_end(List_ptr list, int value)
{

  if (list->head == NULL)
  {
    return add_to_start(list, value);
  }

  Node_ptr new_node = create_node(value);

  if (new_node == NULL)
  {
    return Failure;
  }

  list->last->next = new_node;
  list->last = new_node;
  ++list->count;
  return Success;
}

Status insert_at(List_ptr list, int value, int position)
{
  if (position == 0)
  {
    return add_to_start(list, value);
  }

  if (position == list->count)
  {
    return add_to_end(list, value);
  }

  Node_ptr node_before_position = get_nth_node(list, (position - 1));
  if (node_before_position == NULL)
  {
    return Failure;
  }

  Node_ptr new_node = create_node(value);
  new_node->next = node_before_position->next;
  node_before_position->next = new_node;
  ++list->count;

  return Success;
}

Status add_unique(List_ptr list, int value)
{
  if (has_element(list, value) == Success)
  {
    return Failure;
  }

  return add_to_end(list, value);
  ;
}

Status remove_from_start(List_ptr list)
{
  if (list->head == NULL)
  {
    return Failure;
  }

  Node_ptr temp = list->head->next;
  free(list->head);
  list->head = temp;
  --list->count;

  if (list->head == NULL)
  {
    list->last = NULL;
  }

  return Success;
}

Status remove_at(List_ptr list, int position)
{
  if (position == 0)
  {
    return remove_from_start(list);
  }

  Node_ptr node_before_position = get_nth_node(list, (position - 1));

  if (node_before_position == NULL)
  {
    return Failure;
  }

  Node_ptr temp = node_before_position->next;
  node_before_position->next = temp->next;
  free(temp);
  --list->count;

  if (list->count == position)
  {
    list->last = node_before_position;
  }

  return Success;
}

Status remove_from_end(List_ptr list)
{
  return remove_at(list, (list->count - 1));
}

Status remove_first_occurrence(List_ptr list, int number)
{
  Node_ptr previous = list->head;

  if (previous == NULL)
  {
    return Failure;
  }

  if (previous->value == number)
  {
    return remove_from_start(list);
  }

  Node_ptr current = previous->next;

  while (current != NULL)
  {

    if (current->value != number)
    {
      previous = current;
      current = current->next;
      continue;
    }

    previous->next = current->next;
    free(current);
    --list->count;

    if (previous->next == NULL)
    {
      list->last = previous;
    }

    return Success;
  }

  return Failure;
}

Status remove_all_occurrences(List_ptr list, int number)
{
  Status stat = Failure;
  Node_ptr previous = NULL, current = list->head;

  while (current != NULL)
  {
    if (current->value != number)
    {
      previous = current;
      current = current->next;
      continue;
    }

    stat = Success;

    if (current == list->head)
    {
      remove_from_start(list);
      current = list->head;
      continue;
    }

    previous->next = current->next;
    free(current);
    --list->count;
    current = previous->next;
  }

  if (previous != list->last)
  {
    list->last = previous;
  }

  return stat;
}

Status clear_list(List_ptr list)
{
  Node_ptr walker = list->head;

  while (walker != NULL)
  {
    Node_ptr temp = walker->next;
    free(walker);
    walker = temp;
  }

  list->head = NULL;
  list->last = NULL;
  list->count = 0;
  return Success;
}

void destroy_list(List_ptr list)
{
  clear_list(list);
  free(list);
}