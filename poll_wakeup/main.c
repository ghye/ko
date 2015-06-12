#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
	int ret;
	int fd;
	unsigned char buf[2];
	fd_set rfd;
	struct timeval time={0, 0};

	fd = open("/dev/pw", O_RDWR);
	if (-1 == fd) {
		perror("open: ");
		return -1;
	}

	read(fd, buf, 2);

	sleep(5);
	FD_ZERO(&rfd);
	FD_SET(fd, &rfd);
	ret = select(fd + 1, &rfd, NULL, NULL, NULL);
	if (ret == 0) {
		printf("timeout.\n");
	} else if (ret == -1) {
		if (errno == EINTR)
			printf("interrupt.\n");
		else
			perror("select err:\n");
	} else {
		if (FD_ISSET(fd, &rfd)) {
			printf("select ok.\n");
		}
	}

	sleep(5);
	FD_ZERO(&rfd);
	FD_SET(fd, &rfd);
	ret = select(fd + 1, &rfd, NULL, NULL, NULL);
	if (ret == 0) {
		printf("timeout.\n");
	} else if (ret == -1) {
		if (errno == EINTR)
			printf("interrupt.\n");
		else
			perror("select err:\n");
	} else {
		if (FD_ISSET(fd, &rfd)) {
			printf("select ok.\n");
		}
	}

	close(fd);
	return 0;
}
