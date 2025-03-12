#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syslimits.h>
#include <dirent.h>
#include <stdlib.h>

// TODO: separate the main loop function into a different file

// TODO: create the functionality for the built-in "cd" command

// TODO: create a simple array that keeps the history of commands the user uses

// TODO: create a simple array of key-value pairs for the alias

int main()
{
	char *commands[] = {"ls", "cd"};
	// Infinite loop
	for (;;) {

		char *command = (char *)malloc(50 * sizeof(char));
		char const target[] = "quit";

		printf("\n$ ");
		scanf("%s", command);

		// Checks if the input string is equal to "quit" to break out of infinite loop
		if (strcmp(command, target) == 0) {
			break;
		}
		else {
			for (int i = 0; i < 2; i++) {
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
					}
					break;
				} else {
					printf("This is not a built-in command!\n");
				}
			}
		}

		free(command);
	}

	return 0;
}
