#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syslimits.h>
#include <stdlib.h>
#include <stdbool.h>

#include "history.h"


// TODO: separate the main loop function into a different file

// TODO: create the functionality for the built-in "cd" command

// Struct for a key-value map with a pointer to the next user element
typedef struct node {
    char *key;
    char *value;
    struct node *next;
} node;

typedef struct {
	node *head;
} linked_list;

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

int main()
{
	char *commands[] = {"ls", "cd", "history", "alias"};
	char *command = (char *)malloc(50 * sizeof(char));

	char *commandHistory[3] = {};

	// Infinite loop
	for (;;) {

		char const target[] = "quit";

		printf("\n$ ");
		fgets(command, 256, stdin);

		command[strcspn(command, "\n")] = '\0';

		// Checks if the input string is equal to "quit" to break out of infinite loop
		if (strcmp(command, target) == 0) {
			break;
		}
		else {
			bool booleanValue = false;

			for (int i = 0; i < 4; i++) {
				if (strcmp(command, commands[i]) == 0) {
					if (strcmp(commands[i], commands[0]) == 0) {

						// Creates a new child process and executes the "ls" command
						const pid_t pid = fork();
						if (pid == 0) {
							char *args[] = {"ls", NULL};
							execvp("/bin/ls", args);
							perror("execution failed!");
							exit(1);
						} else if (pid > 0) {
							waitpid(pid, NULL, 0);
						} else {
							perror("fork failed");
						}

						booleanValue = true;

						if (commandHistory[0] == NULL) {
							commandHistory[0] = commands[i];
						} else {
							commandHistory[1] = commandHistory[0];
							commandHistory[0] = commands[i];
						}
					}

					else if (strcmp(commands[i], commands[1]) == 0) {
						if (commandHistory[0] == NULL) {
							commandHistory[0] = commands[i];
						} else {
							commandHistory[1] = commandHistory[0];
							commandHistory[0] = commands[i];
						}

						booleanValue = true;
					}

					else if (strcmp(commands[i], commands[2]) == 0) {
						printHistory(commandHistory);
						booleanValue = true;
					}

					else if (strcmp(commands[i], commands[3]) == 0) {
						printf("THIS IS AN ALIAS\n");
						booleanValue = true;
					}

					else {
						booleanValue = false;
					}

					break;
				}
			}

            // Lets the user know the command they entered is not valid
            if (booleanValue == false) {
                printf("This is not a built-in command!\n");
            }
		}
	}

	// Deallocates memory for the command the user entered
	free(command);

	return 0;
}
