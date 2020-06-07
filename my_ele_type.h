#ifndef _MY_ELE_TYPE_H_
#define _MY_ELE_TYPE_H_

#include <stdlib.h>
#include <stdio.h>

#define default_data '0'

typedef struct element
{
    void *p_obj;
}element;
typedef struct element * ele_ptr;

void print_element(ele_ptr);

/*
void fill_null_byte(void *_p_start, size_t len)
{
    char *p_start = (char *)_p_start;
    int i = 0;
    char null_byte = '0';
    for (; i < len; ++i)
        p_start[i] = null_byte;
    return;
}
*/

#endif 