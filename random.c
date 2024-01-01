#include "random.h"
#include <unistd.h>
#include <fcntl.h>

int fd; // file descriptor

int init_random() {
	fd = open("/dev/random", O_RDONLY);

	if (fd < 0) {
		return -1;
	}
}

int get_random_uint(unsigned int *number) {
	unsigned int buf[1];
	size_t count = sizeof(buf);
	ssize_t n = read(fd, &buf, count);

	*number = buf[0];

	return n == 0 ? -1 : n;
}

int end_random() {
	close(fd);
}
