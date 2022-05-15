#include "list.h"

void list_append(list_t *list, listnode_t *n) {
  while ((*list) != 0)
    (*list) = (*list)->next;
  (*list) = n;
  n->next = 0;
}

listnode_t *list_pop(list_t *list) {
  listnode_t *n = *list;
  if (*list != 0) {
    *list = (*list)->next;
    n->next = 0;
  }
  return n;
}
