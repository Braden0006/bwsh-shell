//
// Created by Braden Whitcher on 3/18/25.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "shell_functions.h"

int create_process(char **args) {

	pid_t pid = fork();

	if (pid == 0) {
		if (execvp(args[0], args) == -1) {
			perror("execution failed!");
		}

		exit(EXIT_FAILURE);

	}
	else if (pid > 0) {
		waitpid(pid, NULL, 0);
	} else {
		perror("fork failed");
	}

	return -1;
}