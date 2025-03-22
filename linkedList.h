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

// Struct for the linked list to store the nodes
typedef struct {
	node *head;
} linked_list;

// Function that creates a linked list
linked_list *create_list(void);

// Functions that inserts a node into a linked list
void insert(linked_list *list, const char *key, const char *value);

// Function that prints the nodes in a linked list
void print_list(linked_list *list);

// Function that deallocates the memory for a linked list
void free_list(linked_list *list);

#endif //LINKEDLIST_H