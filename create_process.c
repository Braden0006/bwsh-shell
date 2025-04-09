//
// Created by Braden Whitcher on 3/18/25.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "shell_functions.h"

int create_process(char **args) {

	// Initializes variable for separate child process
	const pid_t pid = fork();

	// Makes sure the child process was created successfully
	if (pid == 0) {

		// 'execvp' replaces the current process image with a new program and checks to see if it
		// was created successfully
		if (execvp(args[0], args) == -1) {
			perror("execution failed!");
			exit(EXIT_FAILURE);
		}

	}
	else if (pid > 0) {

		// Makes the parent process wait for the child process to finish
		waitpid(pid, NULL, 0);

		return 0;
	} else {
		perror("fork failed");
	}

	return -1;
}
