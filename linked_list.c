#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#include "shell_functions.h"

// Function for creating a linked list
linked_list *create_list(void) {
	// Dynamically allocates memory for linked list
	linked_list *list = malloc(sizeof(linked_list));

	list->head = NULL;

	return list;
}

// Function for inserting a node into a linked list
void insertAtBeginning(linked_list *list, const char *value) {

	// Dynamically allocates memory for the new node
	Node *new_node = malloc(sizeof(Node));

	// Sets the key, value, and 'next' pointer for a node
	new_node->value = strdup(value);
	new_node->next = list->head;

	list->head = new_node;
}

// Function for printing each node in a linked list
void print_list(linked_list *list) {

	// Node variable for keeping track of the current node
	Node *current = list->head;

	printw("\n");

	// Prints each node in the list until it reaches the end
	while (current) {
		printw("| %s ", current->value);
		current = current->next;
	}

	printw("|\n");
}

// Function for deallocating the memory for a linked list
void free_list(linked_list *list) {

	// Defines a new node variable for keeping track of each node
	Node *current = list->head;

	// Deallocates the memory for each node until it reaches the end of the list
	while (current) {
		Node *temp = current;
		current = current->next;

		free(temp->value);
		free(temp);
	}

	// Deallocates memory for the linked list
	free(list);
}
