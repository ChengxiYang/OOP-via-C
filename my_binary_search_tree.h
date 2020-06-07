#ifndef _MY_BINARY_SEARCH_TREE_H_
#define _MY_BINARY_SEARCH_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include "my_ele_type.h"

#define default_key (0)

typedef struct tree_node_linker
{
    struct tree_node_linker *p_parent;
    struct tree_node_linker *p_left;
    struct tree_node_linker *p_right;
}t_linker;
typedef struct tree_node_linker * t_linker_ptr;

typedef struct binary_tree_node
{
    int key;
    element data;
    t_linker node_linker;
}bt_node;
typedef struct binary_tree_node * bt_node_ptr;

size_t node_linker_offset();
bt_node_ptr linker_to_node(t_linker_ptr);
bt_node_ptr init_bt_node();
void print_bt_node(bt_node_ptr);

struct binary_search_tree;
typedef struct binary_search_tree * bs_tree_ptr;
typedef struct binary_search_tree
{
    int node_num;
    bt_node_ptr p_root;
    
    void (*p_destruct_bs_tree)(bs_tree_ptr);
    void (*p_transplant)(bs_tree_ptr, bt_node_ptr, bt_node_ptr);
    bt_node_ptr (*p_maximum)(bt_node_ptr);
    bt_node_ptr (*p_minimum)(bt_node_ptr);
    void (*p_insert_node)(bs_tree_ptr, ele_ptr, int);
    bt_node_ptr (*p_find_node)(bs_tree_ptr, int);
    void (*p_delete_node)(bs_tree_ptr, int);
    void (*p_level_walk)(bt_node_ptr);
    void (*p_preorder_walk)(bt_node_ptr);
    void (*p_inorder_walk)(bt_node_ptr);
    void (*p_postorder_walk)(bt_node_ptr);
}bs_tree;

void destruct_bs_tree(bs_tree_ptr);
void bs_tree_transplant(bs_tree_ptr, bt_node_ptr, bt_node_ptr);
bt_node_ptr bs_tree_maximum(bt_node_ptr);
bt_node_ptr bs_tree_minimum(bt_node_ptr);
void bs_tree_insert_node(bs_tree_ptr, ele_ptr, int);
bt_node_ptr bs_tree_find_node(bs_tree_ptr, int);
void bs_tree_delete_node(bs_tree_ptr, int);
void bs_tree_level_walk(bt_node_ptr);
void bs_tree_preorder_walk(bt_node_ptr);
void bs_tree_inorder_walk(bt_node_ptr);
void bs_tree_postorder_walk(bt_node_ptr);

#endif