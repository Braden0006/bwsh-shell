#include <ncurses.h>
#include <stdlib.h>

#include "shell_functions.h"

void ncurses_terminal(linked_list *list) {
	int inputChar;

	char *buffer = (char *)malloc(50 * sizeof(char));

	// Initializes scanner
	initscr();

	// Enables arrow keys
	keypad(stdscr, TRUE);

	// Enables vertical scrolling
	scrollok(stdscr, TRUE);

	printw("Press the up arrow to print history\n");
	printw("Press the 'q' key to quit\n");

	refresh();

	Node *current = list->head;

	while ((inputChar = getch()) != 'q') {

		// Checks to see if the key that was pressed is the up arrow
		if (inputChar == KEY_UP) {

			// Prints the value of the current node
			printw("%s | ", current->value);
			
			// Goes to the next one
			current = current->next;

			// Checks to see if it reaches the end of the list
			if (current->next == NULL) {
				printw("\nYou reached the end of the list!\n\n");
				current = list->head;
			}
		}
		refresh();
	}

	printw("\n");

	// Ends scanner
	endwin();
}
