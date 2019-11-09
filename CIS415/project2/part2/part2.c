/*
 * Description:
 *
 * Author: Natalie Letz #951463883
 *
 * Date: 2019-11-04
 *
 * Notes:
 */

#include <sys/syscall.h>
#include <sys/types.h>
#include <libgen.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <wait.h>
#include <time.h>

// Some constants used in various functions
#define AT_FDCWD -100
#define BUF_SIZE 1024
#define READ_BUF_SIZE 1048576

int run = 0;

// Our run signal! Cute huh?
void sigusr1(int signal)
{
	run = 1;
}

void cleanParams(char **params)
{
	for (int i=0; i<BUF_SIZE; ++i) { params[i] = NULL; }
}

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

	// Delimiter & token pointer to be used by strtok()
	const char *delimiter = " \t\n\f\r\v";
	char *token;
	char *command = malloc(sizeof(char) * BUF_SIZE);
	char **params = malloc(sizeof(char *) * BUF_SIZE);
	for (int j=0; j<BUF_SIZE; ++j) { params[j] = NULL; }
	int i = 1;

	// The in / out streams used for writing, by default going
	// to be stdin and stdout
	FILE *instream;
	FILE *outstream;
	int changed = 0;

	// The variables used for getline() calls
	char *line    = 0;
	size_t len    = 0;
	ssize_t nread = 0;

	// Fork and process stuff
	pid_t pid;
	int error, count = 0;
	int status;

	// Timer stuff
	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = 50000L;

	// Setting up the streams and making sure we got a flag
	instream  = stdin;
	outstream = stdout;
	if (argc > 1)
	{
		instream = fopen(argv[1], "r");
		freopen("pseudoshell_output.txt", "w", stdout);
		changed = 1;

		// Check to see if the streams we were given are okay
		if (instream == NULL || outstream == NULL)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "No correct file given.\n");
		exit(EXIT_FAILURE);
	}

	// Make sure our run signal is not erroring us out of
	// the entire program... still free up if it is
	if (signal(SIGUSR1, sigusr1) == SIG_ERR)
	{
		perror("signal");
		mainCleaner(command, params);
		exit(EXIT_FAILURE);
	}

	// Main run loop
	while ((!changed ? printf(">>> ") : 1)
		&& (nread = getline(&line, &len, instream)) != -1)
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
		fprintf(stderr, "Params: %s ", params[0]);
		while (token != NULL)
		{
			token = strtok(NULL, delimiter);
			params[i] = token;
			fprintf(stderr, "%s ", params[i]);
			i++;
		}

		fprintf(stderr, "(command is %s)\n", command);

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			mainCleaner(command, params);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			while (run == 0)
			{
				nanosleep(&tim, &tim2);
			}
			error = execvp(command, params);

			mainCleaner(command, params);
			perror("execvp");
			exit(EXIT_FAILURE);
		}

		// Clean up my stuff to set up for next command and
		// its params
		command = NULL;
		cleanParams(params);
		i = 1;
		count++;
	}

	for (int j=0; j<count; ++j)
	{
		kill(pid, SIGUSR1);
	}

	for (int j=0; j<count; ++j)
	{
		kill(pid, SIGSTOP);
	}

	for (int j=0; j<count; ++j)
	{
		kill(pid, SIGCONT);
	}

	for (int j=0; j<count; ++j)
	{
		waitpid(pid, &status, 0);
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