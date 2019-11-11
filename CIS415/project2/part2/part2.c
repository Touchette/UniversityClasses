/*
 * Description: This part builds on part1 by adding the abiloity
 *		to stop and resume processes with signals, but no new
 *		signal handlers of my own
 *
 * Author: Natalie Letz #951463883
 *
 * Date: 2019-11-04
 *
 * Notes:
 */

#include "part2.h"

// Our run signal! Cute huh?
void sigusr1(int signal)
{
	run = 1;
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
	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = 50000L;

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
	if (signal(SIGUSR1, sigusr1) == SIG_ERR)
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
				nanosleep(&tim, &tim2);
			}

			error = execvp(command, params);

			// Cleanup if we messed up
			mainCleaner(command, params);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		count++;

		// Clean up my stuff to set up for next command and
		// its params
		command = NULL;
		cleanParams(params);
		i = 1;
	}

	// Send the SIGUSR1 signals...
	for (j=0; j<count; ++j)
	{
		fprintf(stdout, "PID %d receiving SIGUSR1\n", pids[j]);
		kill(pids[j], SIGUSR1);
	}

	// ... the SIGSTOP signals...
	for (j=0; j<count; ++j)
	{
		fprintf(stdout, "PID %d receiving SIGSTOP\n", pids[j]);
		kill(pids[j], SIGSTOP);
	}

	// ... the SIGCONT signals...
	for (j=0; j<count; ++j)
	{
		fprintf(stdout, "PID %d receiving SIGCONT\n", pids[j]);
		kill(pids[j], SIGCONT);
	}

	// ... and wait for them to finish
	for (j=0; j<count; ++j)
	{
		waitpid(pids[j], &status, 0);
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