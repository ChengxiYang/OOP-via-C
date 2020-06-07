#ifndef _MY_ARRAY_QUEUE_H_
#define _MY_ARRAY_QUEUE_H_

#include <stdbool.h>
#include "my_array.h"
#include "my_ele_type.h"

struct array_queue;
typedef struct array_queue * arr_queue_ptr;
typedef struct array_queue
{
    array ele_array;            
    int front;    
    int back;
    /* 
        *takes circle array to construct array queue.
        *front always points to element of head of queue.
        *back always points to element of tail of queue.
    */
    bool (*p_double_capacity)(arr_queue_ptr);
    void (*p_push_back)(arr_queue_ptr, ele_ptr);
    void (*p_pop_front)(arr_queue_ptr); 
    ele_ptr (*p_get_front)(arr_queue_ptr);
    ele_ptr (*p_get_back)(arr_queue_ptr);
    void (*p_print_queue)(const arr_queue_ptr);
}array_queue;

void init_array_queue(struct array_queue **, int);
bool arr_queue_double_capacity(arr_queue_ptr);
void arr_queue_push_back(arr_queue_ptr, ele_ptr);
void arr_queue_pop_front(arr_queue_ptr); 
ele_ptr arr_queue_get_front(arr_queue_ptr);
ele_ptr arr_queue_get_back(arr_queue_ptr);
void print_arr_queue(const arr_queue_ptr);

#endif