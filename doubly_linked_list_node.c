#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list_node.h"

// crear un nodo nuevo
dll_node_t* dll_node_new(t_elem value){
  dll_node_t* new_node = (dll_node_t*)malloc(sizeof(dll_node_t));
  if(new_node == NULL){
    printf("memory cannot be reserved for a new dll_node");
    exit(-1);
  }
  new_node->value = value;
  new_node->prev = NULL;
  new_node->next = NULL;
  return new_node;
}

//liberar memoria de un nodo
void dll_node_free(dll_node_t** node){
  if(node != NULL  && *node !=NULL){
    (*node)->next = NULL;
    (*node)->prev = NULL;
    free(*node);
    *node = NULL;
  }
}

//funcion para retornar el valor de un nodo
t_elem dll_node_get_value(dll_node_t* node){
  if(node == NULL){
    printf("dll_node pointer is NULL");
    exit(-2);
  }
  return node->value;
}

//funcion para obtener el nodo anterior
dll_node_t* dll_node_get_prev(dll_node_t* node){
  if(node == NULL){
    printf("dll_node pointer is NULL");
    exit(-3);
  }
  return node->prev;
}

//funcion para obtener el nodo siguiente
dll_node_t* dll_node_get_next(dll_node_t* node){
  if(node == NULL){
    printf("dll_node pointer is NULL");
    exit(-4);
  }
  return node->next;
}

//funcion para obtener la referencia del nodo anterior
dll_node_t** dll_node_get_prev_reference(dll_node_t* node){
  if(node == NULL){
    printf("dll_node pointer is NULL");
    exit(-5);
  }
  return &node->prev;
}

//funcion para obtener la referencia del nodo siguiente
dll_node_t** dll_node_get_next_reference(dll_node_t* node){
  if(node == NULL){
    printf("dll_node pointer is NULL");
    exit(-6);
  }
  return &node->next;
}

//procedimiento para concatenar dos nodos.Retorna 1 si se conectaron, 0 en caso contrario(*origin == NULL)
int dll_node_link_node(dll_node_t** origin,dll_node_t** destiny){
  if(origin == NULL){
    printf("dll_node pointer origin is NULL");
    exit(-7);
  }
  if(destiny == NULL){
    printf("dll_node pointer destiny is NULL");
    exit(-8);
  }
  int returned = 0;
  if(*origin != NULL){
    (*origin)->next = *destiny;
    if(*destiny != NULL){
      (*destiny)->prev = *origin;
    }
    returned = 1;
  }
  return returned;
}

//pricedimiento para añadir un nodo al final de una lista
void dll_node_add_node_end(dll_node_t** head,dll_node_t** new_node){
  if(head==NULL){
    printf("dll_node double pointer is null");
    exit(-9);
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

//pricedimiento para añadir un valor al final de una lista
void dll_node_add_value_end(dll_node_t** head,t_elem value){
  if(head==NULL){
    printf("dll_node double pinter is null");
    exit(-10);
  }
  dll_node_t* new_node = dll_node_new(value);
  dll_node_add_node_end(head,&new_node);
}

//pricedimiento para añadir un nodo al inicio de la lista
void dll_node_add_node_first(dll_node_t** head,dll_node_t* new_node){
  if(head==NULL){
    printf("dll_node double pointer is null");
    exit(-11);
  }
  dll_node_t* auxiliar = *head;
  if(*head != NULL){
    auxiliar->prev = new_node;
  }
  *head = new_node;
  new_node->next = auxiliar;
}

//pricedimiento para añadir un valor al inicio de la lista
void dll_node_add_value_first(dll_node_t** head,t_elem value){
  if(head==NULL){
    printf("dll_node double pointer is null");
    exit(-12);
  }
  dll_node_t* new_node = dll_node_new(value);
  dll_node_add_node_first(head,new_node);
}

// busqueda de un valor en una lista. Retorna NULL en caso de no encontrarse.
dll_node_t** dll_node_search(dll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem)){
  if(head == NULL){
    printf("dll_node double pointer is null");
    exit(-13);
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

//remover un valor de la lista
dll_node_t* dll_node_remove(dll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem)){
  if(head == NULL){
    printf("dll_node double pointer is NULL");
    exit(-14);
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

//imprime por pantalla el valor de un nodo
void dll_node_printf(dll_node_t* node,void (*print)(t_elem)){
  if(node == NULL){
    printf("dll_node pointer is NULL\n");
    exit(-15);
  }
  print(node->value);
}

//imprime por pantalla todos los nodos de una lista
void dll_node_printf_all(dll_node_t* head,void (*print)(t_elem)){
  if(head != NULL){
    print(head->value);
    dll_node_printf_all(head->next,print);
  }
}
