/*
 * Description: This part builds on the project by adding an actual
 *		scheduler. It will schedule in a round-robin manner by using
 *		a signal handler, and each process is given a time quantum of
 *		1 second. This can be changed by changing the alarm(1) call in
 *		main() along with its accompanying sleep(1001) call.
 *
 *
 * Author: Natalie Letz #951463883
 *
 * Date: 2019-11-09
 *
 * Notes: I'm not 100% sure if this works properly, but it sure looks
 *	like it to me from the output.
 */

#include "header.h"

// Just checks if a process has exited or not for the signal handler
int checkProcessStatus(pid_t pid)
{
	int status = 0;

	if (waitpid(pid, &status, WNOHANG) == 0)
		return 0;
	else
		return 1;
}

// Our run signal! Cute huh?
void sigusr1(int signal)
{
	run = 1;
}

// The main signal handler function... made liberal use of the pseudocode
// that Jared posted
void sigalrm(int signal)
{
	int status, i;
	pid_t pid;

	// If no proces is running sigalrm handler does nothing
	if (totalRunningProc == 0)
		return;

	fprintf(stdout, "Parent PID%d: caught alarm.\n", getpid());

	// Start handling the signal...
	// ... by stopping the current running process
	while (pids[idx] != 0)
	{
		if (checkProcessStatus(pids[idx]) == 0)
		{
			printf("Parent PID%d: sending stop to %d.\n", getpid(), pids[idx]);
			kill(pids[idx], SIGSTOP);
			idx++;
			break;
		}
		else
		{
			idx++;
		}
	}

	// ... reset if we've gone too high...
	if (idx >= totalProcCount)
		idx = 0;

	// ... start the next process to be run.
	while (pids[idx] != 0)
	{
		if (checkProcessStatus(pids[idx]) == 0)
		{
			printf("Parent PID%d: sending cont to %d.\n", getpid(), pids[idx]);
			kill(pids[idx], SIGCONT);
			break;
		}
		else
		{
			idx++;
		}
	}

}

// This signal is thrown when children exit, so it's used to decrement
// the running count of processes
void sigchld(int signal)
{
	pid_t pid;
	int status, i;

	// Find all our children and check if they're alive
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		if (WIFEXITED(status))
		{
			for (i=0; i<totalProcCount; ++i)
			{
				if (pids[i] == pid)
				{
					// If it's exited, that's one less running process
					totalRunningProc--;
					break;
				}
			}
		}
	}
}

// Used in main to clear up the params before each new command is read in
void cleanParams(char **params)
{
	int i;
	for (i=0; i<BUF_SIZE; ++i) { params[i] = NULL; }
}

// Cleans up the stuff in main()
void mainCleaner(char *command, char** params)
{
	free(command); command = NULL;
	cleanParams(params);
	free(params); params = NULL;
}

/*-----------------------------Program Main----------------------------------*/
int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);

	// Delimiter & token pointer to be used by strtok(), as well
	// as other string stuff we read in with getline()
	const char *delimiter = " \t\n\f\r\v";
	char *token;
	char *command = malloc(sizeof(char) * BUF_SIZE);
	char **params = malloc(sizeof(char *) * BUF_SIZE);
	int j;
	for (j=0; j<BUF_SIZE; ++j) { params[j] = NULL; }
	int i = 1;

	// The in / out streams used for writing, by default going
	// to be stdin and stdout
	FILE *instream;
	FILE *outstream;
	int changed = 0;

	// The variables used for getline() function calls
	char *line    = 0;
	size_t len    = 0;
	ssize_t nread = 0;

	// Fork and process stuff
	int error, count, status = 0;

	// Timer stuff
	struct timespec tim1, tim2;
	tim1.tv_sec = 0;
	tim1.tv_nsec = 50000L;

	// Setting up the streams and making sure we got an input file
	instream  = stdin;
	outstream = stdout;
	if (argc > 1)
	{
		instream = fopen(argv[1], "r");
		changed = 1;

		// Check to see if the streams we were given are okay
		if (instream == NULL || outstream == NULL)
		{
			perror("fopen");
			mainCleaner(command, params);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "No input given.\n");
		mainCleaner(command, params);
		exit(EXIT_FAILURE);
	}

	// Signal subscriptions
	if (signal(SIGUSR1, sigusr1) == SIG_ERR ||
		signal(SIGALRM, sigalrm) == SIG_ERR ||
		signal(SIGCHLD, sigchld) == SIG_ERR)
	{
		perror("signal");
		mainCleaner(command, params);
		exit(EXIT_FAILURE);
	}

	// Main run loop
	while ((nread = getline(&line, &len, instream)) != -1)
	{
		// Tokenize the input string
		token = strtok(line, delimiter);

		// Do nothing if we get empty input
		if (token == NULL)
		{
			continue;
		}

		// First token we get is the command...
		command = token;
		params[0] = token;
		// ... now parse all of its arguments
		while (token != NULL)
		{
			token = strtok(NULL, delimiter);
			params[i] = token;
			i++;
		}

		// Start the process
		pids[count] = fork();
		if (pids[count] < 0)
		{
			perror("fork");
			mainCleaner(command, params);
			exit(EXIT_FAILURE);
		}
		// For the child process to execvp()
		if (pids[count] == 0)
		{
			run = 0;

			// Process waiting for SIGCONT signal
			while (run == 0)
			{
				nanosleep(&tim1, &tim2);
			}

			fprintf(stdout, "Child PID%d: received SIGUSR1, calling exec.\n", getpid());
			error = execvp(command, params);

			// Cleanup if we messed up
			mainCleaner(command, params);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		count++; totalProcCount++; totalRunningProc++;

		// Clean up my stuff to set up for next command and
		// its params
		command = NULL;
		cleanParams(params);
		i = 1;
	}

	fprintf(stdout, "Parent PID%d: sending SIGUSR1 signals.\n", getpid());
	// Send the SIGUSR1 signals...
	for (j=0; j<count; ++j)
	{
		fprintf(stdout, "Child PID%d: receiving SIGUSR1\n", pids[j]);
		kill(pids[j], SIGUSR1);
	}

	fprintf(stdout, "Parent PID%d: sending SIGSTOP signals to all but one.\n", getpid());
	// ... the SIGSTOP signals to all but first process
	for (j=1; j<count; ++j)
	{
		fprintf(stdout, "Child PID%d: receiving SIGSTOP\n", pids[j]);
		kill(pids[j], SIGSTOP);
	}

	while (totalRunningProc > 0)
	{
		alarm(1);

		sleep(1001);
	}

	// Cleanup
	free(line); line = NULL;
	mainCleaner(command, params);
	if (changed)
	{
		fclose(instream);
		fclose(outstream);
	}

	return EXIT_SUCCESS;
}
/*-----------------------------Program End-----------------------------------*/
