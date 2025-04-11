#include <termios.h>
#include <stdio.h>
#include <unistd.h>

// Disables line echoing and line buffering
void enable_raw_mode() {
	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

// Enables line echoing and line buffering 
void disable_raw_mode() {
	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}
