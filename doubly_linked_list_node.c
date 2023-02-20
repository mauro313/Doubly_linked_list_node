#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list_node.h"

/**
 * @brief create a new node.
 * 
 * @param value 
 * @return dll_node_t* 
 */
dll_node_t* dll_node_new(t_elem value){
  dll_node_t* new_node = (dll_node_t*)malloc(sizeof(dll_node_t));
  if(new_node == NULL){
    printf("memory cannot be reserved for a new dll_node");
    exit(EXIT_FAILURE);
  }
  new_node->value = value;
  new_node->prev = NULL;
  new_node->next = NULL;
  return new_node;
}

/**
 * @brief free the memory of a node.
 * 
 * @param node 
 */
void dll_node_free(dll_node_t** node){
  if(node != NULL  && *node !=NULL){
    (*node)->next = NULL;
    (*node)->prev = NULL;
    free(*node);
    *node = NULL;
  }
}

/**
 * @brief return the element of a node.
 * 
 * @param node 
 * @return t_elem 
 */
t_elem dll_node_get_value(dll_node_t* node){
  if(node == NULL){
    printf("\ndll_node pointer is NULL(1)\n");
    exit(EXIT_FAILURE);
  }
  return node->value;
}

/**
 * @brief setter for the element of a node. 
 * 
 * @param node 
 * @param element 
 */
void dll_node_set_value(dll_node_t** node,t_elem element){
  if(node == NULL){
    printf("\ndll_node double pointer is NULL(1)\n");
    return;
  }
  (*node)->value = element;
}

/**
 * @brief getter for the prev of a node.
 * 
 * @param node 
 * @return dll_node_t* 
 */
dll_node_t* dll_node_get_prev(dll_node_t* node){
  if(node == NULL){
    printf("\ndll_node pointer is NULL(2)\n");
    exit(EXIT_FAILURE);
  }
  return node->prev;
}

/**
 * @brief getter for the next of a node.
 * 
 * @param node 
 * @return dll_node_t* 
 */
dll_node_t* dll_node_get_next(dll_node_t* node){
  if(node == NULL){
    printf("\ndll_node pointer is NULL(3)\n");
    exit(EXIT_FAILURE);
  }
  return node->next;
}

/**
 * @brief get the reference of the prev of a node.
 * 
 * @param node 
 * @return dll_node_t** 
 */
dll_node_t** dll_node_get_prev_reference(dll_node_t* node){
  if(node == NULL){
    printf("\ndll_node pointer is NULL(4)\n");
    exit(EXIT_FAILURE);
  }
  return &node->prev;
}

/**
 * @brief get the reference of the next of a node.
 * 
 * @param node 
 * @return dll_node_t** 
 */
dll_node_t** dll_node_get_next_reference(dll_node_t* node){
 if(node == NULL){
    printf("\ndll_node pointer is NULL(5)\n");
    exit(EXIT_FAILURE);
  }
  return &node->next;
}

/**
 * @brief link two nodes. Return true if there were linked and false if *origin is NULL.
 * 
 * @param origin 
 * @param destiny 
 * @return bool 
 */
bool dll_node_link_node(dll_node_t** origin,dll_node_t** destiny){
  if(origin == NULL){
    printf("\ndll_node pointer origin is NULL\n");
    exit(EXIT_FAILURE);
  }
  if(destiny == NULL){
    printf("\ndll_node pointer destiny is NULL\n");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(*origin != NULL){
    (*origin)->next = *destiny;
    if(*destiny != NULL){
      (*destiny)->prev = *origin;
    }
    returned = true;
  }
  return returned;
}

/**
 * @brief add a node at end of a list of double linked nodes.
 * 
 * @param head 
 * @param new_node 
 */
void dll_node_add_node_end(dll_node_t** head,dll_node_t** new_node){
  if(head == NULL){
    printf("\ndll_node double pointer is NULL(2)\n");
    return;
  }
  if(new_node == NULL){
    printf("\ndll_node double pointer new_node is NULL\n");  
    return;
  }
  if(*head == NULL){
    *head = *new_node;
  }
  else{
    if(*head==NULL){
      *head = *new_node;
      if(*new_node != NULL){
        (*new_node)->prev=*head;
      }
    }
    else{
      dll_node_add_node_end(&(*head)->next,new_node);
    }
  }
}


/**
 * @brief add a element to the end of a list of doubly linked nodes.
 * 
 * @param head 
 * @param value 
 */
void dll_node_add_value_end(dll_node_t** head,t_elem value){
  if(head == NULL){
    printf("\ndll_node double pointer is NULL(3)\n");
    return;
  }
  dll_node_t* new_node = dll_node_new(value);
  dll_node_add_node_end(head,&new_node);
}

/**
 * @brief add a node to at begin of a list of doubly linked nodes.
 * 
 * @param head 
 * @param new_node 
 */
void dll_node_add_node_first(dll_node_t** head,dll_node_t* new_node){
  if(head == NULL){
    printf("\ndll_node double pointer is NULL(4)\n");
    return;
  }
  dll_node_t* auxiliar = *head;
  if(*head != NULL){
    auxiliar->prev = new_node;
  }
  *head = new_node;
  new_node->next = auxiliar;
}

/**
 * @brief add a element at the end of a list of doubly linked nodes.
 * 
 * @param head 
 * @param value 
 */
void dll_node_add_value_first(dll_node_t** head,t_elem value){
  if(head == NULL){
    printf("\ndll_node double pointer is NULL(5)\n");
    return;
  }
  dll_node_t* new_node = dll_node_new(value);
  dll_node_add_node_first(head,new_node);
}

/**
 * @brief search a element in a list of doubly linked nodes.Return the reference of
 * the node that contains the value if exist.
 * 
 * @param head 
 * @param value 
 * @param compare 
 * @return dll_node_t** 
 */
dll_node_t** dll_node_search(dll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem)){
  if(head == NULL){
    printf("\ndll_node double pointer is NULL(6)\n");
    exit(EXIT_FAILURE);
  }
  dll_node_t** returned = NULL;
  if(*head != NULL  && compare((*head)->value,value)!=0){
    returned = dll_node_search(&(*head)->next,value,compare);
  }
  else{
    returned = head;
    if(*head == NULL){
      returned = NULL;
    }
  }
  return returned;
}

/**
 * @brief remove a element of a list of doubly linked nodes.Return the node
 * that contains the element if exist.
 * 
 * @param head 
 * @param value 
 * @param compare 
 * @return dll_node_t* 
 */
dll_node_t* dll_node_remove(dll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem)){
  if(head == NULL){
    printf("\ndll_node double pointer is NULL(7)\n");
    exit(EXIT_FAILURE);
  }
  dll_node_t** reference = dll_node_search(head,value,compare);
  dll_node_t* returned = NULL;
  if(*reference != NULL){
    dll_node_t* auxiliar_1 = *reference;
    dll_node_t** auxiliar_2 = &auxiliar_1->next;
    returned = *reference;
    *reference = (*reference)->next;
    returned->next = NULL;
    returned->prev = NULL;
    if(*auxiliar_2 != NULL){
     *auxiliar_2 = auxiliar_1;
    }
    auxiliar_1 = NULL;
    auxiliar_2 = NULL;
  }
  return returned;
}

/**
 * @brief print the element of a node.
 * 
 * @param node 
 * @param print 
 */
void dll_node_printf(dll_node_t* node,void (*print)(t_elem)){
  if(node == NULL){
    printf("dll_node pointer is NULL(6)\n");
    return;
  }
  print(node->value);
}

/**
 * @brief print a list of doubly linked nodes.
 * 
 * @param head 
 * @param print 
 */
void dll_node_printf_all(dll_node_t* head,void (*print)(t_elem)){
  if(head == NULL){
    printf("\ndll_node pointer is NULL");
    return;
  }
  else{
    print(head->value);
    if(head->next != NULL){
      dll_node_printf_all(head->next,print);
    }
  }
}
