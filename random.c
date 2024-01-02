#include "random.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

int fd; // file descriptor

int init_random() {
	fd = open("/dev/random", O_RDONLY);

	if (fd < 0) {
		return -1;
	}
}

int get_random_uint(uint32_t *number) {
	ssize_t n = read(fd, number, 4);

	return n == 0 ? -1 : n;
}

int end_random() {
	close(fd);
}
