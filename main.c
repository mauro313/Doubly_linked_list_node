#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "doubly_linked_list_node.h"

void print_int(t_elem value);
dll_node_t* list_int_sort(int amount);
int compare_int(t_elem value_1,t_elem value_2);
void dll_node_delete_all(dll_node_t** head);
void dll_node_insert_sorted(dll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem));
dll_node_t** dll_node_merge_sorted(dll_node_t** head_1,dll_node_t** head_2,int (*compare)(t_elem,t_elem));

int main(void){
  srand(time(NULL));
  
  //creation of two list of sorted doubly linked nodes.
  dll_node_t* head = list_int_sort(10);
  dll_node_printf_all(head,print_int);
  printf("\n\n");
  dll_node_t* head_2 = list_int_sort(10);
  dll_node_printf_all(head_2,print_int);
  printf("\n\n");
  
  //merge both list in a new one.
  dll_node_t** head_3 = dll_node_merge_sorted(&head,&head_2,compare_int);
  dll_node_printf_all(*head_3,print_int);
  
  //libero toda la memoria
  dll_node_delete_all(head_3);
  return 0;    
}

//*********************EXAMPLES OF PRECEDURES AND FUNTIONS TO TEST THE IMPLEMENTATION***************************//

/**
 * @brief creation of a list of sorted doubly linked nodes.
 * 
 * @param amount 
 * @return dll_node_t* 
 */
dll_node_t* list_int_sort(int amount){
  dll_node_t* head = NULL;
  for(int i=0;i<amount;i++){
    dll_node_insert_sorted(&head,rand()%50,compare_int);  
  }
  return head;
}

/**
 * @brief auxiliar print procedure.
 * 
 * @param value 
 */
void print_int(t_elem value){
  printf(" %i ",value);  
}

/**
 * @brief auxiliar compare procedure.
 * 
 * @param value_1 
 * @param value_2 
 * @return int 
 */
int compare_int(t_elem value_1,t_elem value_2){
  return value_1-value_2;   
}

/**
 * @brief procedure to delete and free memory of all the nodes of a list.
 * 
 * @param head 
 */
void dll_node_delete_all(dll_node_t** head){
  if(*head != NULL){
    dll_node_delete_all(&(*head)->next);  
    if(*head != NULL){
      dll_node_free(head);
    }
  }    
}

/**
 * @brief procedure for the sorted insertion of a doubly linked node in a list.
 * 
 * @param head 
 * @param value 
 * @param compare 
 */
void dll_node_insert_sorted(dll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem)){
  if(head == NULL){
    return;  
  } 
  dll_node_t* new_node = dll_node_new(value);
  if(*head == NULL){
    *head = new_node;   
  }
  else{
    if(compare(value,dll_node_get_value(*head))<=0){
      dll_node_link_node(&new_node,head);
      *head = new_node; 
    }
    else{
      dll_node_t** auxiliar = head;
      while(dll_node_get_next(*auxiliar)!=NULL && compare(dll_node_get_value(dll_node_get_next(*auxiliar)),value)<0){
        auxiliar = dll_node_get_next_reference(*auxiliar); 
      }
      if(dll_node_get_next(*auxiliar) == NULL){
        dll_node_link_node(auxiliar,&new_node);    
      }
      else{
        dll_node_link_node(&new_node,dll_node_get_next_reference(*auxiliar));
        dll_node_link_node(auxiliar,&new_node);
      }
    }
  }
}

/**
 * @brief merge two list of sorted doubly linked nodes.
 * 
 * @param head_1 
 * @param head_2 
 * @param compare 
 * @return dll_node_t** 
 */
dll_node_t** dll_node_merge_sorted(dll_node_t** head_1,dll_node_t** head_2,int (*compare)(t_elem,t_elem)){
  dll_node_t** returned = NULL;
  if(*head_2 == NULL){
    returned = head_1;
  }
  else{
    if(*head_1 == NULL){
      returned = head_2;
    }
    else{
      if(compare(dll_node_get_value(*head_1),dll_node_get_value(*head_2))<0){
        returned = head_1;
        dll_node_link_node(returned,dll_node_merge_sorted(dll_node_get_next_reference(*head_1),head_2,compare));
      }
      else{
        returned = head_2;
        dll_node_link_node(returned,dll_node_merge_sorted(head_1,dll_node_get_next_reference(*head_2),compare)); 
      }
    }    
  }
  return returned;  
}
