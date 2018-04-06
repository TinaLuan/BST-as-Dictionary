/* COMP20003 Assignment01 Binary search tree operations 1
 * The dictionary is a BST.
 * Every record is a node. Dividing nodes to two groups: <= and >
 * Duplicates handling: all goes to the left (same as the smaller node)
 * written by Tian Luan, Sep. 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictops_1.h"

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
    /* Create a new node for the name and its data */
    node_t *new = (node_t *)safe_malloc(sizeof(node_t));
    node_t *node = dict->root;
    new->name = name;
    new->data = data;
    new->left = new->right = NULL;

    /* The first insertion */
    if (node == NULL) {
        dict->root = new;
        return dict;
    }
    /* Find the parent node of the new node interatively
       The smaller and equal goes to the left; The larger goes to the right */
    while (node) {
        if (strcmp(new->name, node->name) <= 0) {
            if (node->left) {
                node = node->left;
            } else {
                break;
            }
        } else {
            if (node->right) {
                node = node->right;
            } else {
                break;
            }
        }
    }
    /* Insert the new node as the child */
    if (strcmp(new->name, node->name) <= 0) {
        node->left = new;
    } else {
        node->right = new;
    }
    return dict;
}

/* Search the key and write the data directly to the file (for saving space);
   Returns 1 if found; returns 0 if not found */
int
search_dict(dict_t *dict, char *key, FILE *output_file, int *num_cmp) {
    /* Make sure the dictionary exits */
    check_dict(dict);
    node_t *node = dict->root;
    int found = 0, outcome;

    /* Search the whole tree to the end.
       If found, write all data to the file */
    while(node) {
        outcome = strcmp(key, node->name);
        (*num_cmp)++;
        if (outcome < 0) {
            node = node->left;
        } else if (outcome > 0) {
            node = node->right;
        } else {
            found = 1;
            fprintf(output_file, "%s --> %s\n", key, node->data);
            node = node->left;
        }
    }
    return found;
}

/* Release the memory for every name, data, node and dict itself */
static void free_dict_rec(node_t *root);
static void
free_dict_rec(node_t *root) {
    if (root) {
        free_dict_rec(root->left);
        free_dict_rec(root->right);
        free(root->name);
        free(root->data);
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

/* Make sure to malloc successfully */
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
