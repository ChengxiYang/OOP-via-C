#ifndef _MY_ARRAY_H_
#define _MY_ARRAY_H_

#include "my_ele_type.h"
#include <stdbool.h>

typedef struct array
{
    int ele_num; 
    int capa; 
    ele_ptr p_begin;
    /* 
        *number of elements in array.
        *capacity of dynamic_array, and assure that capa >= ele_num >= 0 holds.
        *p_begin ALWAYS points to first element in nonempty array.
        *p_begin keeps fixed if function double_capacity is not called! 
    */
    bool (*p_double_capacity)(struct array *);
    void (*p_insert_element)(struct array *, ele_ptr, int);
    void (*p_push_back)(struct array *, ele_ptr);

    ele_ptr (*p_get_element)(struct array *, int);
    ele_ptr (*p_get_front)(struct array *);
    ele_ptr (*p_get_back)(struct array *);

    void (*p_delete_element)(struct array *, int);
    void (*p_pop_front)(struct array *);
    void (*p_pop_back)(struct array *);
}array;
typedef struct array * array_ptr;

void init_array(struct array **, int);
bool arr_double_capacity(array_ptr);
void arr_insert_element(array_ptr, ele_ptr, int);
void arr_push_back(array_ptr, ele_ptr);
ele_ptr arr_get_element(array_ptr, int);
ele_ptr arr_get_front(array_ptr);
ele_ptr arr_get_back(array_ptr);
void arr_delete_element(array_ptr, int);
void arr_pop_front(array_ptr);
void arr_pop_back(array_ptr);

#endif
