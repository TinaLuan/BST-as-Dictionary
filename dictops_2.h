/* COMP20003 Assignment01 header file for dictops_2.c
 * written by Tian Luan, Sep. 2016
 */
#include <stdio.h>

/* type definitions */
typedef struct node node_t;
typedef struct list list_t;
struct node {
    char *name;
    char *data;
    node_t *next;
};
struct list {
    node_t *head;
    list_t *left;
    list_t *right;
};
typedef struct {
    list_t *root;
} dict_t;

/* function prototypes */
dict_t *make_empty_dict(void);
dict_t *insert_dict(dict_t *dict, char *name, char *data);
int search_dict(dict_t *dict, char *key, FILE *output_file, int *num_cmp) ;
void free_dict(dict_t *dict);
void *safe_malloc(int size);
void check_dict(dict_t *dict);
