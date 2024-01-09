#include "random.h"
#include <sys/random.h>
#include <stdint.h>

int fd; // file descriptor

int init_random() {
	return 0;
}

int get_random_uint(uint32_t *number) {
	ssize_t n = getrandom(number, 4, 0);

	return n == 0 ? -1 : n;
}

int end_random() {
	return 0;
}
