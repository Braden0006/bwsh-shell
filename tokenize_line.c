//
// Created by Braden Whitcher on 3/18/25.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char **tokenize_line(char *command) {
	char *delimiter = " ";
	int buffersize = 64;

	char **tokens = malloc(buffersize * sizeof(char));
	int token_count = 0;

	char *token = strtok(command, delimiter);

	while (token != NULL) {
		tokens[token_count] = token;
		token = strtok(NULL, delimiter);

		token_count++;
	}

	return (tokens);
}