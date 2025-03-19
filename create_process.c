//
// Created by Braden Whitcher on 3/18/25.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "shell_functions.h"

int create_process(char **args) {

	const pid_t pid = fork();

	if (pid == 0) {

		if (execvp(args[0], args) == -1) {
			perror("execution failed!");
		}

		exit(EXIT_FAILURE);

	}
	else if (pid > 0) {
		waitpid(pid, NULL, 0);

		// If the second argument for a command that starts with 'cd' is valid, then execute it
		if (chdir(args[1]) != 0) {
            chdir(args[1]);
		}
	} else {
		perror("fork failed");
	}

	return -1;
}