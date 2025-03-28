#include <termios.h>
#include <stdio.h>
#include <unistd.h>

void rawInput() {
	struct termios t;

	// Gets the current terminal attributes
	tcgetattr(STDIN_FILENO, &t);
	
	// Disables canonical and echo mode
	t.c_lflag &= ~(ICANON | ECHO);

	// Applies changes
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void disableRawInput() {
	struct termios t;

	tcgetattr(STDIN_FILENO, &t);
	
	// Enables canonical and echo mode
	t.c_lflag |= (ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int callFunctions() {
	char c;

	rawInput();

	printf("Press any key (q to quit): \n");

	while (1) {
		read(STDIN_FILENO, &c, 1);
		printf("You pressed: %c\n", c);

		if (c == 'q') {
			break;
		}
	}

	disableRawInput();

	return 0;
}
