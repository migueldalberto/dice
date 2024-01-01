#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

	int fd = open("/dev/random", O_RDONLY);
  
	if (fd < 0) {
		fprintf(stderr, "could not open /dev/random\n");
		return 1;
	}

	for (int i = 0; i < arg_count; ++i) {
		// dice values
		// dice values index -> dvi
		// 0 - number of dice 
		// 1 - number of sides
		// 2 - modifier

		char dice_values[3][8];
		int modifier_sign = 1; // 1 or -1 

		int dvi = 0;
		int j = 0; // dice_cmd index
		int k = 0; // dice value char index

		char *dice_cmd = args[i];

		do {
			if (dice_cmd[j] == 'd') {
				++dvi;
				k = 0;
			} else if (dice_cmd[j] == '+' || dice_cmd[j] == '-') {
				if (dice_cmd[j] == '-') {
					modifier_sign = -1;
				}
				++dvi;
				k = 0;
			} else {
				dice_values[dvi][k] = dice_cmd[j];
				++k;
			}

			++j;
		} while (dice_cmd[j] != '\0');

		int number_of_dice 	= atoi(dice_values[0]);
		number_of_dice 		= number_of_dice == 0 ? 1 : number_of_dice; // d20 = 1d20, not 0d20
		int number_of_sides = atoi(dice_values[1]);
		int modifier 		= atoi(dice_values[2]) * modifier_sign;

		printf("number_of_dice -> %d\n", number_of_dice);
		printf("number_of_sides -> %d\n", number_of_sides);
		printf("modifier -> %d\n", modifier);

		if (number_of_sides == 0) {
			fprintf(stderr, "incorrect dice format, try 2d6 or d20\n");
			return 1;
		}

		int sum = 0;

		printf("%s -> ", dice_cmd);

		for (int k = 0; k < number_of_dice; ++k) {
			unsigned int buf[1];
			size_t count = sizeof(buf);
			ssize_t n = read(fd, &buf, count);

			if (n == 0) {
				fprintf(stderr, "failed reading /dev/random\n");
				return 1;
			}

			unsigned int res = (buf[0] % number_of_sides) + 1;
			sum += res;

			printf("%d ", res);
		}

		char result_str[100];

		if (modifier == 0) {
			sprintf(result_str, "= %d\n", sum);
		} else {
			sprintf(result_str, "(%d%+d) = %d\n", sum, modifier, sum + modifier);
		}

		printf(result_str);
	}

	close(fd);

	return 0;
}
