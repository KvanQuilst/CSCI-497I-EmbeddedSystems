#pragma once

typedef struct listnode_st listnode_t;
typedef listnode_t *list_t;

struct listnode_st {
  struct listnode_st *next;
  struct listnode_st *end;
};

void list_append(list_t *list, listnode_t *n);
listnode_t *list_pop(list_t *list);
