//
// Created by Braden Whitcher on 3/18/25.
//

#ifndef SHELL_FUNCTIONS_H
#define SHELL_FUNCTIONS_H

typedef struct {
      char *key;
      char *value;
} item;

// Struct for a key-value map with a pointer to the next user element
typedef struct Node {
    char *value;
    struct Node *next;
} Node;

// Struct for the linked list to store the nodes
typedef struct {
	Node *head;
} linked_list;

// Function that creates a linked list
linked_list *create_list(void);

// Functions that inserts a node into a linked list
void insertAtBeginning(linked_list *list, const char *value);

// Function that prints the nodes in a linked list
void print_list(linked_list *list);

// Function that deallocates the memory for a linked list
void free_list(linked_list *list);

// Deals with the main, infinite loop
void main_loop(char *command);

// Prints the history of commands
void printHistory(char *input[]);

// Function for creating and executing a new process
int create_process(char **args);

// Tokenizes a line entered by the user
char **tokenize_line(char *line);

void ncurses_terminal(linked_list *list);

void sqlite_add_record(char *command);

void sqlite_check_command(item commands[], int num_commands);

void sqlite_delete_record(char *command);

#endif //SHELL_FUNCTIONS_H
