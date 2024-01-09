#include "random.h"
#include <stdint.h>

#ifdef _WIN32
#include <time.h> 
#include <stdlib.h> 

int init_random() {
	srand(time(NULL));
	return 0;
}

int get_random_uint(uint32_t *number) {
	*number = rand(); 
	return 0;
}

int end_random() {
	return 0;
}

#else
#include <sys/random.h>

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

#endif
