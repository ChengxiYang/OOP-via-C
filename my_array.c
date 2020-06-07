#include <stdio.h>
#include <stdlib.h>
#include "my_array.h"

void init_array(struct array **pp_arr, int _capa)
{
    if (_capa < 1) {
        printf("initialize_array: invalid argument!\n");
        return;
    }
    *pp_arr = (array_ptr)malloc(sizeof(array));
    if ((*pp_arr) == NULL) {
        printf("initialize_array: \
        failure to construct array object!\n");
        return;
    }
    else {
        (*pp_arr)->ele_num = 0;
        (*pp_arr)->capa = _capa;
        (*pp_arr)->p_begin = (ele_ptr)calloc((*pp_arr)->capa, sizeof(element));
        if ((*pp_arr)->p_begin == NULL) {
            printf("initialize_array: \
            failure to allocate memmory for array object!\n");
            return;
        }
        (*pp_arr)->p_double_capacity = &arr_double_capacity;
        (*pp_arr)->p_insert_element = &arr_insert_element;
        (*pp_arr)->p_push_back = &arr_push_back;
        (*pp_arr)->p_get_element = &arr_get_element;
        (*pp_arr)->p_get_front = &arr_get_front;
        (*pp_arr)->p_get_back = &arr_get_back;
        (*pp_arr)->p_delete_element = &arr_delete_element;
        (*pp_arr)->p_pop_front = &arr_pop_front;
        (*pp_arr)->p_pop_back = &arr_pop_back;
        return;
    }
}

bool arr_double_capacity(array_ptr p_arr)
{
    p_arr->capa = 2 * p_arr->capa;
    ele_ptr p_src = p_arr->p_begin;
    ele_ptr p_dest = (ele_ptr)calloc(p_arr->capa, sizeof(element));
    if (p_dest == NULL) {
        printf("double_capacity: \
        failure to double capacity of array object!\n");
        return false;
    }
    else {
        int i = 0, len = p_arr->ele_num;
        for (; i < len; ++i)
            p_dest[i] = p_src[i];
        p_arr->p_begin = p_dest;
        free(p_src);
        return true;
    }
}

void arr_insert_element(array_ptr p_arr, ele_ptr p_ele, int index)
{
    if (index < 0 || index > p_arr->ele_num) {
        printf("insert: index out of range!\n");
        return;
    }
    if (p_arr->ele_num == p_arr->capa) {
        bool flag = p_arr->p_double_capacity(p_arr);
        if (flag == false) {
            printf("arr_insert_element: failure to double capacity!\n");
            return;
        }
    }
    int k = p_arr->ele_num - 1; 
    for (; k >= index; --k) 
        (p_arr->p_begin)[k + 1] = (p_arr->p_begin)[k];
    //p_ele->p_print_ele = &print_element;
    (p_arr->p_begin)[index] = *p_ele;
    p_arr->ele_num += 1;
    return;
}

void arr_push_back(array_ptr p_arr, ele_ptr p_ele)
{
    p_arr->p_insert_element(p_arr, p_ele, p_arr->ele_num);
    return;
}

ele_ptr arr_get_element(array_ptr p_arr, int index)
{
    if (index < 0 || index > (p_arr->ele_num - 1)) {
        printf("get_element: index out of range!\n");
        return NULL;
    }
    return (p_arr->p_begin + index);
}

ele_ptr arr_get_front(array_ptr p_arr)
{
    return p_arr->p_get_element(p_arr, 0);
}

ele_ptr arr_get_back(array_ptr p_arr)
{
    return p_arr->p_get_element(p_arr, (p_arr->ele_num - 1));
}

void arr_delete_element(array_ptr p_arr, int index)
{
    if (p_arr->ele_num == 0) {
        printf("delete_element: empty array!\n");
        return;
    }
    if (index < 0 || index > (p_arr->ele_num - 1)) {
        printf("delete_element: index out of range!\n");
        return;
    }
    int k = index + 1, ele_num = p_arr->ele_num;
    for (; k < ele_num; ++k)
        (p_arr->p_begin)[k - 1] = (p_arr->p_begin)[k];
    //do nothing in case of deleting element at right boundary!
    p_arr->ele_num -= 1;
}

void arr_pop_front(array_ptr p_arr)
{
    p_arr->p_delete_element(p_arr, 0);
    return;
}

void arr_pop_back(array_ptr p_arr)
{
    p_arr->p_delete_element(p_arr, (p_arr->ele_num - 1));
    return;
}

