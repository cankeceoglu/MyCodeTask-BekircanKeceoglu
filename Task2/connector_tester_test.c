#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "ioctl_test.h"

int main() {
	int answer;
	int dev = open("/dev/connector_tester", O_WRONLY);
	if(dev == -1) {
		printf("Opening was not possible!\n");
		return -1;
	}

	ioctl(dev, 1, &answer);
	printf("Connector no %d\n", answer);
	
	ioctl(dev, 2, &answer);
	printf("Connector no %d\n", answer);
	
	ioctl(dev, 3, &answer);
	printf("Connector no %d\n", answer);

	close(dev);
	return 0;
}
