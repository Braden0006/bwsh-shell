//
// Created by Braden Whitcher on 3/17/25.
//

#include "shellLoop.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/syslimits.h>
#include <unistd.h>
#include <stdlib.h>

#include "history.h"

void main_loop(char *command, char *commands[], char *commandHistory[]) {

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
				if (strstr(command, commands[i]) != NULL) {

					// Checks to see if the user command starts with 'ls'
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

					// Checks to see if the user command starts with 'cd'
					else if (strcmp(commands[i], commands[1]) == 0) {
						if (commandHistory[0] == NULL) {
							commandHistory[0] = commands[i];
						} else {
							commandHistory[1] = commandHistory[0];
							commandHistory[0] = commands[i];
						}

						booleanValue = true;
					}

					// Checks to see if the user command start with 'history'
					else if (strcmp(commands[i], commands[2]) == 0) {
						printHistory(commandHistory);
						booleanValue = true;
					}

					// Checks to see if the user command starts with 'alias'
					else if (strstr(commands[i], commands[3]) != NULL) {
						char *token;
						char *delimiter = " ";

						char *tokens[3] = {};
						int token_count = 0;

						token = strtok(command, delimiter);

						while (token != NULL && token_count < 3) {
							tokens[token_count] = strdup(token);
							printf("Token: %s\n", token);
							token = strtok(NULL, delimiter);

							token_count++;
						}

						for (int i = 0; i < 3; i++) {
							printf("%s", tokens[i]);
						}
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
}
