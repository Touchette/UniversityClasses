#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	pid_t c_pid, pid;

	c_pid = fork();
	if (c_pid == 0)
	{
		printf("child pid is: %d\n", pid);
		execvp(argv[1], NULL);
	}
	else if (c_pid > 0)
	{
		pid = wait(&status);
		printf("parent finished\n");
	}
	else
	{
		printf("fork failed\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}
