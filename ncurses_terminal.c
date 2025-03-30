#include <ncurses.h>

#include "shell_functions.h"

void ncurses_terminal(linked_list *list) {
	int ch;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	printw("Press the up arrow to print history\n");
	printw("Press the 'q' key to quit\n");
	refresh();

	while ((ch = getch()) != 'q') {
		switch (ch) {
			case KEY_UP:
				print_list(list);
				break;
			default:
				printw("Other key was pressed: %d\n", ch);
				break;
		}
		refresh();
	}
	endwin();
}
