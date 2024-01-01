#ifndef ROLL_H
#define ROLL_H

typedef struct {
	char *cmd;
	int amount;
	int sides;
	int modifier;
	int *results;
	int results_sum;
} roll_t;

int parse_roll (char *str, roll_t *roll);
int do_roll (roll_t *roll);
void print_roll (roll_t *roll);

#endif
