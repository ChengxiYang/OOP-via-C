#ifndef _MY_ARRAY_STACK_H_
#define _MY_ARRAY_STACK_H_

#include "my_array.h"
#include "my_ele_type.h"

struct array_stack;
typedef struct array_stack * arr_stack_ptr;
typedef struct array_stack
{
    array_ptr p_ele_arr;
    //int back;

    void (*p_push_back)(arr_stack_ptr, ele_ptr);
    ele_ptr (*p_get_back)(arr_stack_ptr);
    void (*p_pop_back)(arr_stack_ptr);
}array_stack;

void init_array_stack(struct array_stack **, int);
void arr_stack_push_back(arr_stack_ptr, ele_ptr);
ele_ptr arr_stack_get_back(arr_stack_ptr);
void arr_stack_pop_back(arr_stack_ptr);

#endif