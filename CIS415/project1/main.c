/*
 * Description:
 * A very basic bash emulator that can simulate a few commands. It implements
 * ls, pwd, mkdir, cd, cp, mv, and rm. All of the functions are implemented
 * solely with syscalls, any string manipulation is done with strcat and
 * strcmp (or manually). Accepts input in both a command-line mode and a
 * file-reading mode via use of execution flags.
 *
 * Author: Natalie Letz #951463883
 *
 * Date: 2019-10-11
 *
 * Notes:
 * 1. ls is implemented via getdents and not the calls listed on Piazza (I
 * wrote the function before the lab or the Piazza post being made).
 * 2. I don't think that the program is very efficient nor very performant.
 * This is in part due to how many loops and branches I use (way too many) as
 * well as my lack of splitting repeated code into functions. I tried to do so,
 * but continually ran into memory problems (leaks, etc.) and didn't think it
 * worth the hassle to optimize.
 * 3. I don't like C strings.
 */

/*-------------------------Preprocessor Directives---------------------------*/
#include <sys/syscall.h>
#include <sys/types.h>
#include "command.h"
#include <libgen.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

// Some constants used in various functions
#define AT_FDCWD -100
#define BUF_SIZE 1024
#define READ_BUF_SIZE 1048576
/*---------------------------------------------------------------------------*/

// Wraps the functions that take two arguments so that I can minimize
// repeated code within main().
void callFunction(char *command, char *arg1, char *arg2)
{
	// Handle ls
	if (strcmp(command, "ls") == 0)
	{
		if (arg1 == NULL && arg2 == NULL)
		{
			listDir();
			return;
		}
		else
		{
			fprintf(stdout, "Unsupported parameters for ls.\n");
			return;
		}
	}
	// Handle pwd
	else if (strcmp(command, "pwd") == 0)
	{
		if (arg1 == NULL && arg2 == NULL)
		{
			showCurrentDir();
			return;
		}
		else
		{
			fprintf(stdout, "Unsupported parameters for pwd.\n");
			return;
		}
	}
	// Handle mkdir
	else if (strcmp(command, "mkdir") == 0)
	{
		if (arg1 != NULL && arg2 == NULL)
		{
			makeDir(arg1);
			return;
		}
		else
		{
			fprintf(stdout, "Unsupported parameters for mkdir.\n");
			return;
		}
	}
	// Handle cd
	else if (strcmp(command, "cd") == 0)
	{
		if (arg1 != NULL && arg2 == NULL)
		{
			changeDir(arg1);
			return;
		}
		else
		{
			fprintf(stdout, "Unsupported parameters for cd.\n");
			return;
		}
	}
	// Handle cp
	else if (strcmp(command, "cp") == 0)
	{
		if (arg1 != NULL && arg2 != NULL)
		{
			copyFile(arg1, arg2);
			return;
		}
		else
		{
			fprintf(stdout, "Insufficient parameters for cp.\n");
			return;
		}
	}
	// Handle mv
	else if (strcmp(command, "mv") == 0)
	{
		if (arg1 != NULL && arg2 != NULL)
		{
			moveFile(arg1, arg2);
			return;
		}
		else
		{
			fprintf(stdout, "Insufficient parameters for mv.\n");
			return;
		}
	}
	// Handle rm
	else if (strcmp(command, "rm") == 0)
	{
		if (arg1 != NULL && arg2 == NULL)
		{
			deleteFile(arg1);
			return;
		}
		else
		{
			fprintf(stdout, "Unsupported parameters for rm.\n");
			return;
		}
	}
	// Handle cat
	else if (strcmp(command, "cat") == 0)
	{
		if (arg1 != NULL && arg2 == NULL)
		{
			displayFile(arg1);
			return;
		}
		else
		{
			fprintf(stdout, "Unsupported parameters for cat.\n");
			return;
		}
	}
}

// Checks if a given string is a valid command
int checkCommand(char *cmd)
{
	if (cmd == NULL)
		return 0;
	else if (strcmp(cmd, "ls") == 0)
		return 1;
	else if (strcmp(cmd, "pwd") == 0)
		return 1;
	else if (strcmp(cmd, "mkdir") == 0)
		return 1;
	else if (strcmp(cmd, "cd") == 0)
		return 1;
	else if (strcmp(cmd, "cp") == 0)
		return 1;
	else if (strcmp(cmd, "mv") == 0)
		return 1;
	else if (strcmp(cmd, "rm") == 0)
		return 1;
	else if (strcmp(cmd, "cat") == 0)
		return 1;
	else if (strcmp(cmd, "exit") == 0)
		return 1;
	else
		return 0;
}

// Checks if a given string is a control code
int checkControl(char *ch)
{
	if (ch == NULL)
		return 0;
	else if (strcmp(ch, ";") == 0)
		return 1;
	else
		return 0;
}
/*---------------------------------------------------------------------------*/

/*-----------------------------Program Main----------------------------------*/
int main(int argc, char *argv[])
{
	setbuf(stdout, NULL);

	// Delimiter & token pointer to be used by strotok()
	const char *delimiter = " \t\n\f\r\v";
	char *token;
	char *command = malloc(sizeof(char) * BUF_SIZE);
	char *param1  = malloc(sizeof(char) * BUF_SIZE);
	char *param2  = malloc(sizeof(char) * BUF_SIZE);

	// The in / out streams used for writing, by default going
	// to be stdin and stdout
	FILE *instream;
	FILE *outstream;
	int changed = 0;

	// The variables used for getline() calls
	char *line    = 0;
	size_t len    = 0;
	ssize_t nread = 0;

	// Setting up the streams and flags for the shell
	instream  = stdin;
	outstream = stdout;
	if (argc > 1)
	{
		// If we got multiple args then it's filemode...
		if (argc > 2)
		{
			if (strcmp(argv[1], "-f") == 0)
			{
				instream = fopen(argv[2], "r");
				freopen("pseudoshell_output.txt", "w", stdout);
				changed = 1;

				// Check to see if the streams we were given are okay
				if (instream == NULL || outstream == NULL)
				{
					perror("fopen");
					exit(EXIT_FAILURE);
				}
			}
			// ... but maybe not? Make sure it was -f flag
			else
			{
				fprintf(stderr, "Too many args without -f flag.\n");
				exit(EXIT_FAILURE);
			}
		}
		// If we got one arg, it's gotta be "-command", otherwise we
		// don't continue.
		else if (strcmp(argv[1], "-command") != 0)
		{
			fprintf(stderr, "No correct startup flags given.\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "No startup flags given.\n");
		exit(EXIT_FAILURE);
	}

	// Main run loop
	while ((!changed ? printf(">>> ") : 1)
		&& (nread = getline(&line, &len, instream)) != -1)
	{
		// Tokenize the input string
		token = strtok(line, delimiter);

		label1:
		// check if token is a command here else continue
		if (checkCommand(token))
		{
			strcpy(command, token);
		}
		else
		{
			fprintf(stdout, "Error: unrecognized command.\n");
			continue;
		}

		// Exit successfully if we get an exit command
		if (token != NULL)
		{
			if (strcmp(token, "exit") == 0)
			{
				fprintf(stdout, "\n");
				break;
			}
		}
		// Do nothing if we get empty input
		else if (token == NULL)
		{
			continue;
		}

		// Given output has a newline before displaying the tokens
		printf("\n");
		while (token != NULL)
		{
			token = strtok(NULL, delimiter);
			if (checkCommand(token) == 1)
			{
				fprintf(stdout, "Error: incorrect syntax; no control code found.\n");
				break;
			}
			else if (checkControl(token) || token == NULL)
			{
				callFunction(command, NULL, NULL);
				break;
			}
			else
			{
				strcpy(param1, token);
				token = strtok(NULL, delimiter);
				if (checkCommand(token))
				{
					fprintf(stdout, "Error: incorrect syntax; no control code found.\n");
					break;
				}
				else if (checkControl(token) || token == NULL)
				{
					callFunction(command, param1, NULL);
					break;
				}
				else
				{
					strcpy(param2, token);
					callFunction(command, param1, param2);
					break;
				}
			}
		}

		token = strtok(NULL, delimiter);
		if (checkCommand(token))
		{
			goto label1;
		}
	}

	// Cleanup
	free(line); line = NULL;
	free(command); command = NULL;
	free(param1); param1 = NULL;
	free(param2); param2 = NULL;
	if (changed)
	{
		fclose(instream);
		fclose(outstream);
	}

	return EXIT_SUCCESS;
}
/*-----------------------------Program End-----------------------------------*/
