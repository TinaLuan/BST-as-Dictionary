#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictops_2.h"

#define NAME_LEN         64
#define DATA_LEN         1465
#define DELIMITER        ','
#define NOT_FOUND_MSG    "NOTFOUND"

FILE *safe_open(char *filename, char *mode);
void read_and_insert(FILE *input_file, dict_t *dict);
void search_and_write(dict_t *dict, FILE *output_file);

int
main(int argc, char *argv[]) {
    /* Get command arguments */
    char *input_fname = argv[1];
    char *output_fname = argv[2];
    if (!input_fname || !output_fname) {
        printf("Lack of arguments\n");
        exit(EXIT_FAILURE);
    }

    /* Read the input file and build the dictionary */
    FILE *input_file = safe_open(input_fname, "r");
    dict_t *dict = make_empty_dict();
    read_and_insert(input_file, dict);
    fclose(input_file);

    /* Search the key name and write into the output file */
    FILE *output_file = safe_open(output_fname, "w");
    search_and_write(dict, output_file);
    fclose(output_file);

    free_dict(dict);

    return 0;
}

/* Make sure to open the file successfully */
FILE
*safe_open(char *filename, char *mode) {
    FILE *file = fopen(filename, mode);
    if (!file) {
        printf("Fail to open %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

/* Read the input file and build the dictionary */
void
read_and_insert(FILE *input_file, dict_t *dict) {
    char line[NAME_LEN+DATA_LEN+3]; /* count \0, \n and comma */
    char temp[NAME_LEN+1]; /* count \0 */
    char *name, *data;
    int name_len, data_len, i;

    /* Read the file line by line including \0, \n and comma */
    while (fgets(line, NAME_LEN+DATA_LEN+3, input_file)) {
        name_len = data_len = i = 0;
        while(line[i] != DELIMITER) {
            temp[name_len++] = line[i++];
        }
        temp[name_len++] = '\0';

        /* Store the name and data */
        name = (char *)safe_malloc(sizeof(char) * name_len);
        strcpy(name, temp);
        i += 1; /* skip the comma */
        data_len = strlen(line+i) + 1; /* count \0 and \n as well */
        data = (char *)safe_malloc(sizeof(char) * data_len);
        strcpy(data, line+i);

        /* Insert into the dictionary */
        dict = insert_dict(dict, name, data);
    }
}

/* Search the key name and write into the output file */
void
search_and_write(dict_t *dict, FILE *output_file) {
    char c, key[NAME_LEN+1];
    int num_cmp, i, j;

    /* Get the key(s) */
    while ((c = getchar())!=EOF) {
        num_cmp = i = j = 0;
        key[i++] = c;
        while ((c= getchar()) != '\n' && (c!=EOF)) {
            key[i++] = c;
        }
        key[i] = '\0';
        /* Has found nothing, write the message to output file */
        if(!search_dict(dict, key, output_file, &num_cmp)) {
            fprintf(output_file, "%s --> %s\n", key, NOT_FOUND_MSG);
        }
        /* Give out the number of comparisons to stdout */
        printf("%s --> %d\n", key, num_cmp);
    }
}
