//
// Created by Braden Whitcher on 3/18/25.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char **tokenize_line(char *command) {
	const char *delimiter = " ";
	int buffersize = 64;

	// Dynamically allocated array that stores each word after they are sepeerated
	char **tokens = malloc(buffersize * sizeof(char));
	int token_count = 0;

	char *token = strtok(command, delimiter);

	// For each word in a line, add it to the 'tokens' array
	while (token != NULL) {
		tokens[token_count] = token;
		token = strtok(NULL, delimiter);

		token_count++;
	}

	return (tokens);
}