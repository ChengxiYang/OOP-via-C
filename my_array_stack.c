#include <stdlib.h>
#include "my_array_stack.h"

void init_array_stack(struct array_stack **pp_arr_stack,
                      int _capa)
{
    (*pp_arr_stack) = (arr_stack_ptr)malloc(sizeof(array_stack));
    /*
    *wrong implementation!
    array_ptr p_ele_arr = (*pp_arr_stack)->p_ele_arr;
    init_array(&p_ele_arr, _capa);
    */
    struct array **pp_ele_arr = &((*pp_arr_stack)->p_ele_arr);
    init_array(pp_ele_arr, _capa);
    (*pp_arr_stack)->p_push_back = &arr_stack_push_back;
    (*pp_arr_stack)->p_get_back = &arr_stack_get_back;
    (*pp_arr_stack)->p_pop_back = &arr_stack_pop_back;
}

void arr_stack_push_back(arr_stack_ptr p_arr_stack, ele_ptr p_ele)
{
    (p_arr_stack->p_ele_arr)->p_push_back(p_arr_stack->p_ele_arr, p_ele);
}

ele_ptr arr_stack_get_back(arr_stack_ptr p_arr_stack)
{
    (p_arr_stack->p_ele_arr)->p_get_back(p_arr_stack->p_ele_arr);
}

void arr_stack_pop_back(arr_stack_ptr p_arr_stack)
{
    (p_arr_stack->p_ele_arr)->p_pop_back(p_arr_stack->p_ele_arr);
}