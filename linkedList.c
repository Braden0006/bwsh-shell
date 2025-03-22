//
// Created by Braden Whitcher on 3/17/25.
//

#include "linkedList.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Function for creating a linked list
linked_list *create_list(void) {

	// Dynamically allocates memory for linked list
	linked_list *list = malloc(sizeof(linked_list));

	list->head = NULL;

	return list;
}

// Function for inserting a node into a linked list
void insert(linked_list *list, const char *key, const char *value) {

	// Dynamically allocates memory for the new node
	node *new_node = malloc(sizeof(node));

	// Sets the key, value, and 'next' pointer for a node
	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->next = list->head;

	list->head = new_node;
}

// Function for printing each node in a linked list
void print_list(linked_list *list) {

	// Node variable for keeping track of the current node
	node *current = list->head;

	// Prints each node in the list until it reaches the end
	while (current) {
		printf("%s: %s\n", current->key, current->value);
		current = current->next;
	}
}

// Function for deallocating the memory for a linked list
void free_list(linked_list *list) {

	// Defines a new node variable for keeping track of each node
	node *current = list->head;

	// Deallocates the memory for each node until it reaches the end of the list
	while (current) {
		node *temp = current;
		current = current->next;

		free(temp->key);
		free(temp->value);
		free(temp);
	}

	// Deallocates memory for the linked list
	free(list);
}
