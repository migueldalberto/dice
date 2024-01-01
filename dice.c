#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int arg_count = 0;
char *args[10];

int main (int argc, char **argv) {

	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			int j = 1;

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
		int j = 0;
		bool d_reached = false;
		bool sign_reached = false;
		char dice_count_str[8];
		int dice_count_str_i = 0;
		char dice_sides_str[8];
		int dice_sides_str_i = 0;
		char modifier_str[8];
		int modifier_str_i = 0;
		int modifier_sign = 1;

		while (args[i][j] != '\0') {
			if (sign_reached) {
				modifier_str[modifier_str_i] = args[i][j];
				++modifier_str_i;
			} else if (args[i][j] == '+' || args[i][j] == '-') {
				if (args[i][j] == '-') {
					modifier_sign = -1;
				}
				sign_reached = true;
			} else if (d_reached) {
				dice_sides_str[dice_sides_str_i] = args[i][j];
				++dice_sides_str_i;
			} else if (args[i][j] == 'd') {
				d_reached = true;
			} else {
				dice_count_str[dice_count_str_i] = args[i][j];
				++dice_count_str_i;
			}

			++j;
		}

		dice_count_str[dice_count_str_i] = '\0';
		dice_sides_str[dice_sides_str_i] = '\0';
		modifier_str[modifier_str_i] 	 = '\0';

		int dice_count = atoi(dice_count_str);
		dice_count = dice_count == 0 ? 1 : dice_count;

		int dice_sides = atoi(dice_sides_str);
		int modifier = atoi(modifier_str) * modifier_sign;

		if (dice_sides == 0) {
			fprintf(stderr, "incorrect dice format, try 2d6 or d20\n");
			return 1;
		}

		int sum = 0;

		char dice_str[dice_count_str_i + dice_sides_str_i + modifier_str_i + 3];

		if (modifier == 0) {
			sprintf(dice_str, "%dd%d", dice_count, dice_sides);
		} else {
			sprintf(dice_str, "%dd%d%+d", dice_count, dice_sides, modifier);
		}

		printf("%s -> ", dice_str);

		for (int k = 0; k < dice_count; ++k) {
			unsigned int buf[1];
			size_t count = sizeof(buf);
			ssize_t n = read(fd, &buf, count);

			if (n == 0) {
				fprintf(stderr, "failed reading /dev/random\n");
				return 1;
			}

			unsigned int res = (buf[0] % dice_sides) + 1;
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
