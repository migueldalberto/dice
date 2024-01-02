#ifndef ROLL_H
#define ROLL_H

#include <stdint.h>

typedef struct {
	char *cmd;
	uint32_t amount;
	uint32_t sides;
	int32_t modifier;
	uint32_t *results;
	uint32_t results_sum;
} roll_t;

int parse_roll (char *str, roll_t *roll);
int do_roll (roll_t *roll);
void print_roll (roll_t *roll);

#endif
