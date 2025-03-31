#include <ncurses.h>

#include "shell_functions.h"

void ncurses_terminal(linked_list *list) {
	int inputChar;

	// Initializes scanner
	initscr();

	// Enables arrow keys
	keypad(stdscr, TRUE);

	// Enables vertical scrolling
	scrollok(stdscr, TRUE);

	printw("Press the up arrow to print history\n");
	printw("Press the 'q' key to quit\n");

	while ((inputChar = getch()) != 'q') {
		switch (inputChar) {
			case KEY_UP:
				print_list(list);
				break;
			default:
				printw("Other key was pressed: %d\n", inputChar);
				break;
		}
	}

	// Ends scanner
	endwin();
}
