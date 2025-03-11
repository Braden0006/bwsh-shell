#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syslimits.h>
#include <dirent.h>

void show_files() {
	DIR *d;
	struct dirent *dir;

	d = opendir(".");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (dir->d_type == DT_REG) {
				printf("%s    ", dir->d_name);
			}
		}

		closedir(d);
	}
}

int main()
{
	char *built_commands[] = {"ls", "cd"};

	// Infinite loop
	for (;;) {
		char command[50];
		char const target[] = "quit";

		printf("\n$ ");
		scanf("%s", command);

		// Checks if the input string is equal to "quit" to break out of infinite loop
		if (strcmp(command, target) == 0) {
			break;
		}
		else {
			for (int i = 0; i < 2; i++) {
				if (strcmp(command, built_commands[i]) == 0) {
					if (strcmp(built_commands[i], built_commands[0]) == 0) {
						show_files();
					}
					break;
				} else {
					printf("This is not a built-in command!\n");
				}
			}
		}
	}

	return 0;
}
