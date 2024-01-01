#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "random.h"
#include "roll.h"

int arg_count = 0;
char *args[10];

void handle_args (int argc, char **argv) {
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			int j = 1;

			// the following is for implementing flags, maybe an advantage flag
			while (argv[i][j] != '\0') {
				switch (argv[i][j]) {
					default:
						break;
				}
				++j;
			}
		} else {
			args[arg_count] = argv[i];
			++arg_count;
		}
	}
}

int main (int argc, char **argv) {
	handle_args(argc, argv);

	if (arg_count == 0) {
		fprintf(stderr, "no dice specified, try d6 or 2d20\n");
		return 1;
	}

	if (init_random() < 0) {
		fprintf(stderr, "failed to initialize pseudorng\n");
		return 1;
	}

	for (int i = 0; i < arg_count; ++i) {
		char *dice_cmd = args[i];
		roll_t roll;

		if (parse_roll(dice_cmd, &roll) < 0) {
			fprintf(stderr, "invalid roll format :(\n");
			return 1;
		}

		if (do_roll(&roll) < 0) {
			fprintf(stderr, "failed to get random number :(\n");
			return 1;
		}

		print_roll(&roll);

		free(roll.results); // ;)
	}

	end_random();

	return 0;
}
