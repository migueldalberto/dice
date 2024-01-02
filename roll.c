#include "roll.h"
#include "random.h"
#include <stdlib.h>
#include <stdio.h>

int parse_roll (char *str, roll_t *roll) {
	char numbers_read[3][20];
	// 0 - amount
	// 1 - sides
	// 2 - mod
	
	for (int i = 0; i < 3; ++i) {
		numbers_read[i][19] = '\0';
	}

	int i = 0;
	int j = 0;
	int k = 0;

	int modifier_sign = 1;

	while (str[i] != '\0') {
		if (str[i] - '0' < 0 || str[i] - '9' > 0) {
			switch (str[i]) {
				case 'd':
					if (j != 0) 
						return -1;
					k = 0;
					++j;
					break;
				case '+':
					if (j != 1) 
						return -1;
					k = 0;
					++j;
					break;
				case '-':
					if (j != 1) 
						return -1;
					modifier_sign = -1;
					k = 0;
					++j;
					break;
				default:
					return -1;
					break;
			}
		} else {
			numbers_read[j][k] = str[i];
			++k;
		}

		++i;
	}

	uint32_t amount = atoi(numbers_read[0]);
	uint32_t sides 	= atoi(numbers_read[1]);
	int32_t  mod	= atoi(numbers_read[2]) * modifier_sign;

	roll->amount 	= amount == 0 ? 1 : amount;
	roll->sides 	= sides;
	roll->modifier 	= mod;
	roll->cmd 		= str;

	return 0;
}

int do_roll (roll_t *roll) {
	roll->results = (uint32_t *) malloc(roll->amount * sizeof(uint32_t));
	roll->results_sum = 0;

	for (int k = 0; k < roll->amount; ++k) {
		uint32_t random_number;

		if (get_random_uint(&random_number) < 0)
			return -1;

		uint32_t res = (random_number % roll->sides) + 1;
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
