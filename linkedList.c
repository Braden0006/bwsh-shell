//
// Created by Braden Whitcher on 3/17/25.
//

#include "linkedList.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

linked_list *create_list(void) {

	// Dynamically allocates memory for linked list
	linked_list *list = malloc(sizeof(linked_list));

	list->head = NULL;

	return list;
}

void insert(linked_list *list, const char *key, const char *value) {
	node *new_node = malloc(sizeof(node));

	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->next = list->head;

	list->head = new_node;
}
void print_list(linked_list *list) {
	node *current = list->head;

	while (current) {
		printf("%s: %s\n", current->key, current->value);
		current = current->next;
	}
}
void free_list(linked_list *list) {
	node *current = list->head;

	while (current) {
		node *temp = current;
		current = current->next;

		free(temp->key);
		free(temp->value);
		free(temp);
	}
	free(list);
}
