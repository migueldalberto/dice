#include "roll.h"
#include "random.h"
#include <stdlib.h>
#include <stdio.h>

int parse_roll (char *str, roll_t *roll) {
		// dice values
		// dice values index -> dvi
		// 0 - number of dice 
		// 1 - number of sides
		// 2 - modifier

		char dice_values[3][8];
		int modifier_sign = 1; // 1 or -1 

		int dvi = 0;
		int j = 0; // str index
		int k = 0; // dice value char index

		do {
			if (str[j] == 'd') {
				++dvi;
				k = 0;
			} else if (str[j] == '+' || str[j] == '-') {
				if (str[j] == '-') {
					modifier_sign = -1;
				}
				++dvi;
				k = 0;
			} else if (str[j] - 48 < 0 || str[j] - 57 > 0) {
				return -1;
			} else {
				dice_values[dvi][k] = str[j];
				++k;
			}

			++j;
		} while (str[j] != '\0');

		int number_of_dice 	= atoi(dice_values[0]);
		number_of_dice 		= number_of_dice == 0 ? 1 : number_of_dice; // d20 = 1d20, not 0d20
		int number_of_sides = atoi(dice_values[1]);
		int modifier 		= atoi(dice_values[2]) * modifier_sign;

		if (number_of_sides == 0) {
			return -1;
		}

		roll->amount 	= number_of_dice;
		roll->sides 	= number_of_sides;
		roll->modifier 	= modifier;
		roll->cmd 		= str;

		return 0;
}

int do_roll (roll_t *roll) {
	roll->results = (int *) malloc(roll->amount * sizeof(int));
	roll->results_sum = 0;

	for (int k = 0; k < roll->amount; ++k) {
		unsigned int random_number;

		if (get_random_uint(&random_number) < 0)
			return -1;

		int res = (random_number % roll->sides) + 1;
		roll->results[k] = res;
		roll->results_sum += res;
	}

}

void print_roll (roll_t *roll) {
	printf("%s -> ", roll->cmd);

	for (int i = 0; i < roll->amount; ++i) {
		printf("%d ", roll->results[i]);
	}

	char result_str[100];

	if (roll->modifier == 0) {
		sprintf(result_str, "= %d\n", roll->results_sum);
	} else {
		sprintf(
				result_str, 
				"(%d%+d) = %d\n", 
				roll->results_sum, 
				roll->modifier, 
				roll->results_sum + roll->modifier
				);
	}

	printf(result_str);
}
