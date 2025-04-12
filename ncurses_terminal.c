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

	// Disable echoing
	//noecho();

	printw("Press the up arrow to print history\n");
	printw("Press the 'q' key to quit\n");

	refresh();

	Node *current = list->head;

	while ((inputChar = getch()) != 'q') {
		if (inputChar == KEY_UP) {
			//print_list(list);
			printw("%s | ", current->value);
			current = current->next;
		} else {
			getstr(buffer);
			printw("You entered: %s\n", buffer);
		}
		refresh();
	}

	// Ends scanner
	endwin();
}
