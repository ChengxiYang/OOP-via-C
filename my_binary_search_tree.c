#include <stdio.h>
#include <stdlib.h>
#include "my_array_queue.h"
#include "my_array_stack.h"
#include "my_binary_search_tree.h"

//#define _RECURSIVE_WALK_
#define default_tree_nodes 16

size_t node_linker_offset()
{ 
    bt_node_ptr p_node = (bt_node_ptr)malloc(sizeof(bt_node));
    t_linker_ptr p_linker = &(p_node->node_linker);
    size_t offset = (size_t)((char *)p_linker - (char *)p_node);
    return offset;
}

bt_node_ptr linker_to_node(t_linker_ptr p_linker)
{
    if (p_linker == NULL) return NULL;
    size_t offset = node_linker_offset();
    bt_node_ptr p_node = (bt_node_ptr)((char *)p_linker - offset);
    return p_node;
}

bt_node_ptr init_bt_node()
{
    bt_node_ptr p_node = (bt_node_ptr)malloc(sizeof(bt_node));
    if (p_node == NULL) {
        printf("initialize_node: failure to allocation memmory!\n");
        return p_node;
    }
    p_node->key = default_key;
    p_node->data.p_obj = NULL;
    (p_node->node_linker).p_parent = NULL;
    (p_node->node_linker).p_left = NULL;
    (p_node->node_linker).p_right = NULL;
    return p_node;
}

void print_bt_node(bt_node_ptr p_node)
{
    printf("(%d, ", p_node->key);
    print_element(&(p_node->data));
    printf(")\t");
}
bs_tree_ptr init_bs_tree()
{
    bs_tree_ptr p_tree = (bs_tree_ptr)malloc(sizeof(bs_tree));
    if (p_tree == NULL) {
        printf("initialize_bs_tree: failure to allocate memmory!\n");
        return NULL;
    }
    p_tree->node_num = 0;
    p_tree->p_root = NULL; 

    p_tree->p_destruct_bs_tree = &destruct_bs_tree;
    p_tree->p_transplant = &bs_tree_transplant;
    p_tree->p_maximum = &bs_tree_maximum;
    p_tree->p_minimum = &bs_tree_minimum;
    p_tree->p_insert_node = &bs_tree_insert_node;
    p_tree->p_find_node = &bs_tree_find_node;
    p_tree->p_delete_node = &bs_tree_delete_node;
    p_tree->p_level_walk = &bs_tree_level_walk;
    p_tree->p_preorder_walk = &bs_tree_preorder_walk;
    p_tree->p_inorder_walk = &bs_tree_inorder_walk;
    p_tree->p_postorder_walk = &bs_tree_postorder_walk;
    return p_tree;
}

void destruct_bs_tree(bs_tree_ptr p_tree)
{
    return;
}

void bs_tree_transplant(bs_tree_ptr p_tree, bt_node_ptr p_u, bt_node_ptr p_v)
{ //transplantion of different subtree within a specific tree
    if (p_u == NULL || p_v == NULL) {
        printf("transplant: invalid arguments!\n");
        return;
    }
    if (p_u == p_tree->p_root) {
        (p_v->node_linker).p_parent = NULL;
        p_tree->p_root = p_v; 
        //leave node_num to be handled by caller
        //how to obtain number of nodes in a tree by tree walking?
        return;
    }
    if (&(p_v->node_linker) == (p_v->node_linker).p_parent->p_left)
        (p_v->node_linker).p_parent->p_left = NULL;
    else
        (p_v->node_linker).p_parent->p_right = NULL;
    if (&(p_u->node_linker) == (p_u->node_linker).p_parent->p_left)
        (p_u->node_linker).p_parent->p_left = &(p_v->node_linker);
    else
        (p_u->node_linker).p_parent->p_right = &(p_v->node_linker);
    (p_v->node_linker).p_parent = (p_u->node_linker).p_parent;
    (p_u->node_linker).p_parent = NULL;
}

bt_node_ptr bs_tree_maximum(bt_node_ptr p_node)
{
    if (p_node == NULL) {
        printf("tree_maximum: invalid argument!\n");
        return NULL;
    }
    t_linker_ptr p_curr = &(p_node->node_linker);
    t_linker_ptr p_prev = NULL;
    while (p_curr != NULL) {
        p_prev = p_curr;
        p_curr = p_curr->p_right;
    }
    bt_node_ptr p_max_node = linker_to_node(p_prev);
    return p_max_node;
}

bt_node_ptr bs_tree_minimum(bt_node_ptr p_node)
{
    if (p_node == NULL) {
        printf("minimum: invalid calling!\n");
        return NULL;
    }
    t_linker_ptr p_curr = &(p_node->node_linker);
    t_linker_ptr p_prev = NULL;
    while (p_curr != NULL) {
        p_prev = p_curr;
        p_curr = p_curr->p_left;
    }
    bt_node_ptr p_min_node = linker_to_node(p_prev);
    return p_min_node;
}

void bs_tree_insert_node(bs_tree_ptr p_tree, 
                         ele_ptr p_ele, int key)
{
    bt_node_ptr p_new_node = init_bt_node();
    if (p_new_node == NULL) {
        printf("insert_node: unsuccessfully initialize node!\n");
        return;
    }
    p_new_node->data = *p_ele; 
    //(p_new_node->data).p_obj = p_ele->p_obj;
    p_new_node->key = key;
    if (p_tree->node_num == 0) {
        p_tree->p_root = p_new_node; 
        ++(p_tree->node_num);
        return;
    }
    t_linker_ptr p_curr = &((p_tree->p_root)->node_linker);
    t_linker_ptr p_prev = NULL;
    while (p_curr != NULL) {
        p_prev = p_curr;
        if (key <= linker_to_node(p_curr)->key)
            p_curr = p_curr->p_left;
        else
            p_curr = p_curr->p_right;
    }
    if (key <= linker_to_node(p_prev)->key)
        p_prev->p_left = &(p_new_node->node_linker);
    else
        p_prev->p_right = &(p_new_node->node_linker);
    (p_new_node->node_linker).p_parent = p_prev;
    ++(p_tree->node_num);
}

bt_node_ptr bs_tree_find_node(bs_tree_ptr p_tree, int key)
{
    bt_node_ptr p_node = p_tree->p_root;
    t_linker_ptr p_curr = &(p_node->node_linker);
    while (p_curr != NULL && key != p_node->key) {
        if (key < p_node->key)
            p_curr = p_curr->p_left;
        if (key > p_node->key)
            p_curr = p_curr->p_right;
        p_node = linker_to_node(p_curr); 
    }
    return p_node;
}

void bs_tree_delete_node(bs_tree_ptr p_tree, int key)
{
    if (p_tree->node_num == 0) {
        printf("delete_node: empty tree!\n");
        return;
    }
    bt_node_ptr p_delete = bs_tree_find_node(p_tree, key);
    if (p_delete == NULL) {
        printf("delete_node: unexisted node!\n");
        return;
    } //p_delete is root?
    t_linker_ptr p_x = NULL;
    if ((p_delete->node_linker).p_left == NULL) {
        p_x = (p_delete->node_linker).p_right; //p_x could be null pointer
        if (p_delete == p_tree->p_root) {
            p_tree->p_root = linker_to_node(p_x);
            if (p_x != NULL)
                p_x->p_parent = NULL;
        }
        else {
            if (&(p_delete->node_linker) == 
                ((p_delete->node_linker).p_parent)->p_left) 
                ((p_delete->node_linker).p_parent)->p_left = p_x;
            else
                ((p_delete->node_linker).p_parent)->p_right = p_x;
            if (p_x != NULL)
                p_x->p_parent = (p_delete->node_linker).p_parent;  
        }
    }
    else if ((p_delete->node_linker).p_right == NULL) {
        p_x = (p_delete->node_linker).p_left; //p_x cannot be null pointer
        if (p_delete == p_tree->p_root) {
            p_tree->p_root = linker_to_node(p_x);
            p_x->p_parent = NULL;
        }
        else {
            if (&(p_delete->node_linker) == 
                ((p_delete->node_linker).p_parent)->p_left) 
                ((p_delete->node_linker).p_parent)->p_left = p_x;
            else
                ((p_delete->node_linker).p_parent)->p_right = p_x;
            p_x->p_parent = (p_delete->node_linker).p_parent;
        }
    }
    else {
        bt_node_ptr p_y = 
        bs_tree_minimum(linker_to_node((p_delete->node_linker).p_right));
        t_linker_ptr p_y_linker = &(p_y->node_linker);
        p_x = p_y_linker->p_right;
        if (&(p_delete->node_linker) != p_y_linker->p_parent) {
            if (p_x == NULL) {
                if (p_y_linker == (p_y_linker->p_parent)->p_left)
                    (p_y_linker->p_parent)->p_left = NULL;
                else
                    (p_y_linker->p_parent)->p_right = NULL;
                p_y_linker->p_parent = NULL;
            }
            else
                bs_tree_transplant(p_tree, p_y, linker_to_node(p_x));
            p_y_linker->p_right = (p_delete->node_linker).p_right;
            ((p_delete->node_linker).p_right)->p_parent = p_y_linker;
        }
        bs_tree_transplant(p_tree, p_delete, p_y); //p_root could be modified!
        p_y_linker->p_left = (p_delete->node_linker).p_left;
        ((p_delete->node_linker).p_left)->p_parent = p_y_linker;
    }
    free(p_delete); p_delete = NULL;
    --(p_tree->node_num);
}

void bs_tree_level_walk(bt_node_ptr p_bt_node)
{
    if (p_bt_node == NULL) {
        printf("bs_tree_level_walk: empty tree!\n");
        return;
    }
    bt_node_ptr p_curr_node = p_bt_node;
    t_linker_ptr p_curr_linker = &(p_curr_node->node_linker);
    ele_ptr p_curr_ele = NULL;
    element temp_ele;
    temp_ele.p_obj = p_curr_linker;
    arr_queue_ptr p_linker_queue; 
    init_array_queue(&p_linker_queue, default_tree_nodes);
    p_linker_queue->p_push_back(p_linker_queue, &temp_ele);
    printf("path of level walk:\n");

    while ((p_linker_queue->ele_array).ele_num != 0) {
        p_curr_ele = p_linker_queue->p_get_front(p_linker_queue);
        p_linker_queue->p_pop_front(p_linker_queue);
        p_curr_linker = (t_linker_ptr)(p_curr_ele->p_obj);
        if (p_curr_linker->p_left != NULL) {
            temp_ele.p_obj = p_curr_linker->p_left;
            p_linker_queue->p_push_back(p_linker_queue, &temp_ele);
        }
        if (p_curr_linker->p_right != NULL) {
            temp_ele.p_obj = p_curr_linker->p_right;
            p_linker_queue->p_push_back(p_linker_queue, &temp_ele);
        }
        p_curr_node = linker_to_node(p_curr_linker);
        print_bt_node(p_curr_node);
    }
    printf("\n");
}

void bs_tree_preorder_walk(bt_node_ptr p_bt_node)
{
    if (p_bt_node == NULL) {
        printf("bs_tree_level_walk: empty tree!\n");
        return;
    }
    bt_node_ptr p_curr_node = p_bt_node;
    t_linker_ptr p_curr_linker = &(p_curr_node->node_linker);
    t_linker_ptr p_top_linker = NULL;
    //preorder walk of tree starts from root.
    //p_top_linker ALWAYS points to TOP element of p_linker_stack.
    element linker_obj;
    arr_stack_ptr p_linker_stack;
    init_array_stack(&p_linker_stack, default_tree_nodes);
    while (p_curr_linker != NULL) {
        print_bt_node(linker_to_node(p_curr_linker));
        if (p_curr_linker->p_left != NULL) {
            linker_obj.p_obj = p_curr_linker;
            p_linker_stack->p_push_back(p_linker_stack, &linker_obj);
            p_curr_linker = p_curr_linker->p_left;
        }
    }
    if (p_curr_linker->p_right != NULL) {
        linker_obj.p_obj = p_curr_linker;
        p_linker_stack->p_push_back(p_linker_stack, &linker_obj);
        p_curr_linker = p_curr_linker->p_right;
    }
    else {
        p_top_linker = 
        (t_linker_ptr)(p_linker_stack->p_get_back(p_linker_stack))->p_obj;
        p_curr_linker = p_top_linker->p_right; //not right!
    }
}

void bs_tree_inorder_walk(bt_node_ptr p_bt_node)
{
#ifdef _RECURSIVE_WALK_
    if (p_bt_node == NULL)
        return;
    t_linker_ptr p_bt_linker = &(p_bt_node->node_linker);
    if (p_bt_linker->p_left != NULL)
        bs_tree_inorder_walk(linker_to_node(p_bt_linker->p_left));
    print_bt_node(p_bt_node);
    if (p_bt_linker->p_right != NULL)
        bs_tree_inorder_walk((linker_to_node(p_bt_linker->p_right)));
#endif

    if (p_bt_node == NULL) {
        printf("bs_tree_level_walk: empty tree!\n");
        return;
    }
    t_linker_ptr p_curr_linker = &(p_bt_node->node_linker);
    element linker_obj;
    arr_stack_ptr p_linker_stack;
    init_array_stack(&p_linker_stack, default_tree_nodes);
    printf("path of inorder walk:\n");

    while ((p_linker_stack->p_ele_arr)->ele_num > 0 || 
           p_curr_linker != NULL ) {
        while (p_curr_linker != NULL) {
            linker_obj.p_obj = p_curr_linker;
            p_linker_stack->p_push_back(p_linker_stack, &linker_obj);
            p_curr_linker = p_curr_linker->p_left;
        }
        if ((p_linker_stack->p_ele_arr)->ele_num > 0) {
            p_curr_linker = 
            (t_linker_ptr)(p_linker_stack->p_get_back(p_linker_stack))->p_obj;
            p_linker_stack->p_pop_back(p_linker_stack);
            print_bt_node(linker_to_node(p_curr_linker));
            p_curr_linker = p_curr_linker->p_right;
        }
    }
    printf("\n");
}

void bs_tree_postorder_walk(bt_node_ptr p_bt_node)
{

}

