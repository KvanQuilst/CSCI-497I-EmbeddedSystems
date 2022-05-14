#include "list.h"

void list_append(list_t *list, listnode_t *n) {
  if ((*list)->next == 0) {
    (*list)->next = n;
    (*list)->end = n;
  } else {
    n->next = 0;
    (*list)->end->next = n;
    (*list)->end = n;
  }
}

listnode_t *list_pop(list_t *list) {
  listnode_t *n = *list;
  if (*list != 0) {
    *list = (*list)->next;
    n->next = 0;
  }
  return n;
}
