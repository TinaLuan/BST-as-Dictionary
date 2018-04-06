/* COMP20003 Assignment01 Binary search tree operations 2
 * The dictionary is a BST. Every element in the tree is a list_t.
 * Every record is a node. Every list consists of all nodes with the same name.
 * Duplicates handling: all goes to the linked list
 * written by Tian Luan, Sep. 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictops_2.h"

/* Create an empty dictionary */
dict_t
*make_empty_dict(void) {
    dict_t *dict = (dict_t *)safe_malloc(sizeof(dict_t));
    dict->root = NULL;
    return dict;
}

/* Insert the new record in the dictionary */
dict_t
*insert_dict(dict_t *dict, char *name, char *data) {
    /* Make sure the dictionary exits */
    check_dict(dict);
    /* Create the node and list */
    node_t *new_node = (node_t *)safe_malloc(sizeof(node_t));
    list_t *new_list = (list_t *)safe_malloc(sizeof(list_t));
    new_node->name = name;
    new_node->data = data;
    new_node->next = NULL;
    new_list->head = new_node;
    new_list->left = new_list->right = NULL;

    /* The first insertion */
    if (dict->root == NULL) {
        dict->root = new_list;
        return dict;
    }
    /* Find the parent list of the new list interatively
       The smaller goes to the left; The larger goes to the right */
    list_t *list = dict->root;
    int outcome;
    while (list) {
        if ((outcome = strcmp(new_node->name, list->head->name)) < 0) {
            if (list->left) {
                list = list->left;
            } else {
                break;
            }
        } else if (outcome > 0) {
            if (list->right) {
                list = list->right;
            } else {
                break;
            }
        /* A list exists at the correct place, insert the new node as head */
        } else {
            free(new_list);
            new_node->next = list->head;
            list->head = new_node;
            return dict;
        }
    }
    /* No list at the corret place, insert the new list as the child list */
    if (strcmp(new_node->name, list->head->name) < 0) {
        list->left = new_list;
    } else {
        list->right = new_list;
    }
    return dict;
}

/* Search the key and write the data to the file (for saving space);
   Returns 1 if found; returns 0 if not found */
int
search_dict(dict_t *dict, char *key, FILE *output_file, int *num_cmp) {
    /* Make sure the dictionary exits */
    check_dict(dict);
    list_t *list = dict->root;
    node_t *curr_head = NULL;
    int found = 0, outcome;
    *num_cmp = 0;

    /* Search the tree until the first key has been found */
    while(list) {
        outcome = strcmp(key, list->head->name);
        (*num_cmp)++;
        if (outcome < 0) {
            list = list->left;
        } else if (outcome > 0) {
            list = list->right;
        } else {
            found = 1;
            /* Go through the list and write the data to the file */
            curr_head = list->head;
            while(curr_head) {
                fprintf(output_file, "%s --> %s\n", key, curr_head->data);
                curr_head = curr_head->next;
            }
            break;
        }
    }
    return found;
}

/* Release the memory for every name, data, node, list and dict itself */
static void free_dict_rec(list_t *root);
static void
free_dict_rec(list_t *root) {
    node_t *curr_head = NULL;
    if (root != NULL) {
        free_dict_rec(root->left);
        free_dict_rec(root->right);
        /* Free the nodes and the list itself */
        curr_head = root->head;
        while(curr_head) {
            free(curr_head->name);
            free(curr_head->data);
            root->head = curr_head->next;
            free(curr_head);
            curr_head = root->head;
        }
        free(root);
    }
}
void
free_dict(dict_t *dict) {
    /* Make sure the dictionary exits */
    check_dict(dict);
    free_dict_rec(dict->root);
    free(dict);
}


void
*safe_malloc(int size) {
    void *ptr = malloc(size);
    if (!ptr) {
        printf("Fail to malloc\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/* Check if the dict does not exit before doing other operations */
void
check_dict(dict_t *dict) {
    if (!dict) {
        printf("Empty dictionary\n");
        exit(EXIT_FAILURE);
    }
}
