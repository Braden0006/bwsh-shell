//
// Created by Braden Whitcher on 3/17/25.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Struct for a key-value map with a pointer to the next user element
typedef struct node {
    char *key;
    char *value;
    struct node *next;
} node;

typedef struct {
	node *head;
} linked_list;

linked_list *create_list(void);

void insert(linked_list *list, const char *key, const char *value);

void print_list(linked_list *list);

void free_list(linked_list *list);

#endif //LINKEDLIST_H