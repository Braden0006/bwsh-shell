//
// Created by Braden Whitcher on 3/18/25.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char **tokenize_line(char *command) {
	const char *delimiter = " ";
	int bufsize = 64;

	// Dynamically allocated array that stores each word after they are separated
	char **tokens = malloc(bufsize * sizeof(char));

	// Checks to see if the memory allocation for 'tokens' fails
	if (tokens == NULL) {
		free(tokens);
		perror("Memory allocation failed!");
		exit(EXIT_FAILURE);
	}

	int token_count = 0;

	// Takes the first word that is separated by a space
	char *token = strtok(command, delimiter);

	// For each word in a line, add it to the 'tokens' array
	while (token != NULL) {
		tokens[token_count] = token;

		// Checks to see if the amount of words exceeds the buffer size
		if (token_count >= bufsize) {
			bufsize *= 2;

			// Re-allocates memory for the 'tokens' array and stores it in the 'new_tokens' array
			char **new_tokens = realloc(tokens, bufsize * sizeof(char));

			// Checks to see if the memory re-allocation fails
			if (new_tokens == NULL) {
				free(tokens);
				perror("Memory re-allocation failed!");
				exit(EXIT_FAILURE);
			}

			tokens = new_tokens;
		}

		// Continues to the next word that is separated by a space
		token = strtok(NULL, delimiter);

		token_count++;
	}

	tokens[token_count] = NULL;

	return (tokens);
}