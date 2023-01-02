#ifndef DOUBLY_LINKED_LIST_NODE_H_INCLUDED
#define DOUBLY_LINKED_LIST_NODE_H_INCLUDED
#define t_elem int

typedef struct _dll_node{
  t_elem value;
  struct _dll_node* prev;
  struct _dll_node* next;
}dll_node_t;

dll_node_t* dll_node_new(t_elem value);

void dll_node_free(dll_node_t** node);

t_elem dll_node_get_value(dll_node_t* node);

dll_node_t* dll_node_get_prev(dll_node_t* node);

dll_node_t* dll_node_get_next(dll_node_t* node);

dll_node_t** dll_node_get_prev_reference(dll_node_t* node);

dll_node_t** dll_node_get_next_reference(dll_node_t* node);

int dll_node_link_node(dll_node_t** origin,dll_node_t** destiny);

void dll_node_add_node_end(dll_node_t** head,dll_node_t** new_node);

void dll_node_add_value_end(dll_node_t** head,t_elem value);

void dll_node_add_node_first(dll_node_t** head,dll_node_t* new_node);

void dll_node_add_value_first(dll_node_t** head,t_elem value);

dll_node_t** dll_node_search(dll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem));

dll_node_t* dll_node_remove(dll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem));

void dll_node_printf(dll_node_t* node,void (*print)(t_elem));

void dll_node_printf_all(dll_node_t* head,void (*print)(t_elem));

#include "doubly_linked_list_node.c"

#endif // DOUBLY_LINKED_LIST_NODE_H_INCLUDED
