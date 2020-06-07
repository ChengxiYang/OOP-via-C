#include <stdlib.h>
#include <stdio.h>
#include "my_array_queue.h"

void init_array_queue(struct array_queue **pp_arr_queue,
                      int _capa)
{
    if (_capa < 1) {
        printf("initialize_array_queue: invalid argument!\n");
        return;
    }
    (*pp_arr_queue) = (arr_queue_ptr)malloc(sizeof(array_queue));
    if ((*pp_arr_queue) == NULL) {
        printf("initialize_array_queue: failure to construct queue object!\n");
        return;
    }
    ((*pp_arr_queue)->ele_array).capa = _capa; 
    ((*pp_arr_queue)->ele_array).ele_num = 0;
    //initial situation: _capa > 0, ele_num = 0
    ele_ptr p_elements = (ele_ptr)calloc(_capa, sizeof(element));
    if (p_elements == NULL) {
        printf("initialize_array_queue: failure to allocate memmory for elements!\n");
        return;
    }
    ((*pp_arr_queue)->ele_array).p_begin = p_elements;
    ((*pp_arr_queue)->ele_array).p_double_capacity = NULL;
    ((*pp_arr_queue)->ele_array).p_insert_element = NULL;
    ((*pp_arr_queue)->ele_array).p_push_back = NULL;
    ((*pp_arr_queue)->ele_array).p_get_element = NULL;
    ((*pp_arr_queue)->ele_array).p_get_front = NULL;
    ((*pp_arr_queue)->ele_array).p_get_back = NULL;
    ((*pp_arr_queue)->ele_array).p_delete_element = NULL;
    ((*pp_arr_queue)->ele_array).p_pop_front = NULL;
    ((*pp_arr_queue)->ele_array).p_pop_back = NULL;

    (*pp_arr_queue)->front = -1;
    (*pp_arr_queue)->back = -1; //negative integer for empty queue
    (*pp_arr_queue)->p_double_capacity = &arr_queue_double_capacity;
    (*pp_arr_queue)->p_push_back = &arr_queue_push_back;
    (*pp_arr_queue)->p_pop_front = &arr_queue_pop_front;
    (*pp_arr_queue)->p_get_front = &arr_queue_get_front;
    (*pp_arr_queue)->p_get_back = &arr_queue_get_back;
    (*pp_arr_queue)->p_print_queue = &print_arr_queue;
}

bool arr_queue_double_capacity(arr_queue_ptr p_arr_queue)
{
    int cur_capa = (p_arr_queue->ele_array).capa;
    ele_ptr p_src = (p_arr_queue->ele_array).p_begin;
    ele_ptr p_dest = (ele_ptr)calloc(2 * cur_capa, sizeof(element));
    if (p_dest == NULL) {
        printf("arr_queue_double_capacity: ");
        printf("failure to double capacity of queue object!\n");
        return false;
    }
    int i = 0, k = p_arr_queue->front; 
    for (; i < cur_capa; ++i) {
        if (k >= cur_capa)
            k = k % cur_capa;
        p_dest[i] = p_src[k];
        ++k;
    }
    p_arr_queue->front = 0;
    p_arr_queue->back = cur_capa - 1;
    (p_arr_queue->ele_array).p_begin = p_dest;
    (p_arr_queue->ele_array).capa = 2 * cur_capa;
    free(p_src);
    return true;
}

void arr_queue_push_back(arr_queue_ptr p_arr_queue, ele_ptr p_ele)
{
    int ele_num = (p_arr_queue->ele_array).ele_num;
    int capa = (p_arr_queue->ele_array).capa;
    if (ele_num == capa) {
        bool flag = p_arr_queue->p_double_capacity(p_arr_queue);
        if (flag == false) {
            printf("arr_queue_push_back: \
            failure to push new element into tail of queue!\n");
            return;
        }
    }
    if (ele_num == 0) {
        p_arr_queue->front = 0;
        p_arr_queue->back = 0;
        (p_arr_queue->ele_array).p_begin[0] = *p_ele;
    }
    else {
        capa = (p_arr_queue->ele_array).capa;
        /*
         *in case that p_double_capacity was called.
         *update capa to latest value of capacity of queue.
        */
        p_arr_queue->back += 1;
        p_arr_queue->back %= capa;
        int insert_site = p_arr_queue->back;
        (p_arr_queue->ele_array).p_begin[insert_site] = *p_ele;
    }
    (p_arr_queue->ele_array).ele_num += 1;
    return;
}

void arr_queue_pop_front(arr_queue_ptr p_arr_queue)
{
    if ((p_arr_queue->ele_array).ele_num == 0) {
        printf("arr_queue_pop_front: empty queue!\n");
        return;
    }
    if ((p_arr_queue->ele_array).ele_num == 1) {
        p_arr_queue->front = -1;
        p_arr_queue->back = -1;
    }
    else {
        int capa = (p_arr_queue->ele_array).capa;
        p_arr_queue->front += 1;
        p_arr_queue->front %= capa;
    }
    (p_arr_queue->ele_array).ele_num -= 1;
}

ele_ptr arr_queue_get_front(arr_queue_ptr p_arr_queue)
{
    if ((p_arr_queue->ele_array).ele_num == 0) {
        printf("arr_queue_get_front: empty queue!\n");
        return NULL;
    }
    ele_ptr p_start = (p_arr_queue->ele_array).p_begin;
    int ele_site = p_arr_queue->front;
    return p_start + ele_site;
}

ele_ptr arr_queue_get_back(arr_queue_ptr p_arr_queue)
{
    if ((p_arr_queue->ele_array).ele_num == 0) {
        printf("arr_queue_get_back: empty queue!\n");
        return NULL;
    }
    ele_ptr p_start = (p_arr_queue->ele_array).p_begin;
    int ele_site = p_arr_queue->back;
    return p_start + ele_site;
}

void print_arr_queue(const arr_queue_ptr p_arr_queue)
{
    int ele_num = (p_arr_queue->ele_array).ele_num;
    int cur_capa = (p_arr_queue->ele_array).capa;
    ele_ptr p_begin = (p_arr_queue->ele_array).p_begin;
    int i = 0, k = p_arr_queue->front; 
    for (; i < ele_num; ++i) {
        if (k >= cur_capa)
            k = k % cur_capa;
        printf("(%d,", k);
        print_element(p_begin + k);
        printf(")\t");
        ++k;
    }
    printf("\n");
}