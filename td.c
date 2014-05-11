#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "td.h"

/* Returns 0 if deluged is running and 256 if it isn't */
int rc() {
	FILE* fd = popen("ps -e | grep deluged", "r");
	char c;
	while ( (c = (char)fgetc(fd)) != EOF);
	return pclose(fd);
}

int main() {
	pid_t pid, sid;

	pid = fork();
	if (pid < 0) {
		exit(EXIT_FAILURE);
	}
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	umask(0);

	/* Open log */

	sid = setsid();
	if (sid < 0) {
		exit(EXIT_FAILURE);
	}

	if ((chdir("/")) < 0) {
		exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while(1) {
		if (rc() != 0) { /* thus deluged is NOT running */
			FILE* fd = popen("deluged","r");
			pclose(fd);
		}

		sleep(120);
	}

}
