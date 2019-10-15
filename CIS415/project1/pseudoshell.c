/*
 * Description:
 * A very basic bash emulator that can simulate a few
 * commands
 *
 * Author: Natalie Letz #951463883
 *
 * Date: 2019-10-07
 *
 * Notes:
 * This is where my notes would go ... if I HAD ANY
 */

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


// Used for the ls_wrapper function for the getdents syscall
// to work for printing... no idea what's going on tho
struct linux_dirent
{
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

int handleError(int res, const char *callname) 
{
	if (res == -1)
	{
		// Get the errno so I can reference the documentation
		fprintf(stderr, "Error in %s: %d. Problem:\n\t", callname, errno);
		// Get the error output that C provides for more clues
		perror(callname);

		return -1;
	}

	return 0;
}

char * createAbsPath(const char *path)
{
	// Caller needs to free this
	char *cwd = malloc(sizeof(char) * BUF_SIZE);
	
	// Just build the path... kinda self explanatory
	cwd = getcwd(cwd, BUF_SIZE);
	strcat(cwd, "/");
	strcat(cwd, path);

	return cwd;
}

void listDir() 
{
	char *buffer = malloc(sizeof(char) * BUF_SIZE);
	int openat_res, write_res, getdents_res = 0;
	struct linux_dirent *d;
	char d_type;

	// Open the filepath
	openat_res = syscall(SYS_openat, AT_FDCWD, ".", O_DIRECTORY);

	// Handle openat errors if there are any and prematurely exit
	if ((handleError(openat_res, "openat")) == -1)
	{
		free(buffer);
		return;
	}

	do 
	{
		// Make sure to check for errors at the start of every
		// loop, it can't be -1 on the first loop so this is fine
		if (handleError(getdents_res, "getdents") == -1)
		{
			break;
		}

		// Scan the filepath for files
		getdents_res = syscall(SYS_getdents, openat_res, buffer, BUF_SIZE);

		// Print the files according to the documentation on the manpage
		// for getdents (only files, no directories)
		for (int bpos = 0; bpos < getdents_res;)
		{
			// ???
			d = (struct linux_dirent *) (buffer + bpos);
			d_type = *(buffer + bpos + d->d_reclen - 1);

			// Make sure not to print the current directory or the parent directory
			if ((strcmp(d->d_name, ".") != 0) && (strcmp(d->d_name, "..") != 0))
			{
				write_res = syscall(SYS_write, fileno(stdout), strcat(d->d_name, " "), strlen(d->d_name) + 1);
				handleError(write_res, "write");
			}

			bpos += d->d_reclen;
		}
	} while (getdents_res != 0);
	
	// Print the final newline and check for errors one last time
	write_res = syscall(SYS_write, fileno(stdout), "\n", sizeof(char));
	handleError(write_res, "write");

	// Cleanup
	free(buffer);
}

void showCurrentDir()
{
	char *cwd_buffer = malloc(sizeof(char) * BUF_SIZE);
	int getcwd_res, write_res, cwd_len = 0;

	// Get the string that is the current directory name and
	// handle its errors
	getcwd_res = syscall(SYS_getcwd, cwd_buffer, BUF_SIZE);
	handleError(getcwd_res, "getcwd");

	// Create the writeable string
	cwd_len = strlen(cwd_buffer);
	cwd_buffer[cwd_len] = '\n';

	// Write it out to the file and handle its errors
	write_res = syscall(SYS_write, fileno(stdout), cwd_buffer, cwd_len + 1);
	handleError(write_res, "write");

	// Cleanup
	free(cwd_buffer);
}

void makeDir(char *dirName)
{
	mode_t mode = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IROTH);
	int mkdir_res = 0;

	// Create a folder with a mode that allows all users to read to it
	// and write to it, handle its errors
	mkdir_res = syscall(SYS_mkdir, dirName, mode);
	handleError(mkdir_res, "mkdir");
}

void changeDir(char *dirName)
{
	char *cwd = NULL;
	int chdir_res = 0;

	// Constructing the absolute path if we need to
	if (dirName[0] != '/')
	{
		cwd = createAbsPath(dirName);
		chdir_res = syscall(SYS_chdir, cwd);
	}
	// Otherwise we were given an absolute path, do it directly
	else
	{
		chdir_res = syscall(SYS_chdir, dirName);
	}

	// Handle chdir errors
	handleError(chdir_res, "chdir");

	// Cleanup
	free(cwd);
}

void copyFile(char *sourcePath, char *destinationPath)
{
	// Setting up the source path we were given as well as
	// where we're going
	char *read_buffer = malloc(sizeof(char) * READ_BUF_SIZE);
	char *sourcePath_buffer = NULL;
	char *destinationPath_buffer = NULL;

	// Constructing absolute path to the file if needed
	if (sourcePath[0] != '/')
	{
		sourcePath_buffer = createAbsPath(sourcePath);
	}
	// Otherwise just use it
	else
	{
		sourcePath_buffer = sourcePath;
	}
	
	// This is hideously ugly. Gotta make the destination file, which means
	// I need a full path to the file + the "/filename". So, I need to make
	// a string of "/" and append the filename to it... but I need a buffer
	// for "/" or else I won't have enough space to put the rest of the file.
	// So we get this ugly stuff.
	char *destination_filename = malloc(sizeof(char) * BUF_SIZE);
	destination_filename[0] = '/'; 
	strcat(destination_filename, basename(sourcePath_buffer));
	// Why did I have to do that? Memory management sucks sometimes.

	// Constructing the absolute path to the file if needed
	if (destinationPath[0] != '/')
	{
		destinationPath_buffer = createAbsPath(destinationPath);
	}
	// Otherwise just use it
	else
	{
		destinationPath_buffer = destinationPath;
	}

	destinationPath_buffer = strcat(destinationPath_buffer, destination_filename);

	// Normal stuff from other functions
	mode_t read_mode = (S_IRUSR | S_IRGRP | S_IROTH);
	mode_t write_mode = (S_IWUSR | S_IWGRP | S_IWOTH) | read_mode;
	int open_res, read_res, write_res, creat_res, read_len = 0;

	// Open the source file, handle any errors
	open_res = syscall(SYS_open, sourcePath_buffer, O_RDONLY, read_mode);
	handleError(open_res, "open");

	// Read the source file into the buffer
	read_res = syscall(SYS_read, open_res, read_buffer, READ_BUF_SIZE);
	handleError(read_res, "read");
	close(open_res);

	// Open the destination file
	creat_res = syscall(SYS_creat, destinationPath_buffer, write_mode);
	handleError(creat_res, "creat");

	// Write the file into the source destination
	write_res = syscall(SYS_write, creat_res, read_buffer, strlen(read_buffer));
	handleError(write_res, "write");
	close(creat_res);

	// Cleanup
	free(destination_filename);
	free(read_buffer);
	free(sourcePath_buffer);
	free(destinationPath_buffer);
}

void moveFile(char *sourcePath, char *destinationPath) 
{
	// All of this is same as copy basically
	char *sourcePath_buffer = NULL;
	char *destinationPath_buffer = NULL;

	if (sourcePath[0] != '/')
	{
		sourcePath_buffer = createAbsPath(sourcePath);
	}
	else
	{
		sourcePath_buffer = sourcePath;
	}

	char *destination_filename = malloc(sizeof(char) * BUF_SIZE);
	destination_filename[0] = '/'; 
	strcat(destination_filename, basename(sourcePath_buffer));

	if (destinationPath[0] != '/')
	{
		destinationPath_buffer = createAbsPath(destinationPath);
	}
	else
	{
		destinationPath_buffer = destinationPath;
	}
	destinationPath_buffer = strcat(destinationPath_buffer, destination_filename);

	int rename_res = 0;

	rename_res = syscall(SYS_rename, sourcePath_buffer, destinationPath_buffer);
	handleError(rename_res, "rename");


	free(destination_filename);
	free(sourcePath_buffer);
	free(destinationPath_buffer);
}

void deleteFile(char *filename)
{
	char *cwd = NULL;
	int unlink_res = 0;

	// Constructing absolute path to the file if needed
	if (filename[0] != '/')
	{
		cwd = createAbsPath(filename);
		unlink_res = syscall(SYS_unlink, cwd);
	}
	// Otherwise just delete it
	else
	{
		unlink_res = syscall(SYS_unlink, filename);
	}

	// Handle errors
	handleError(unlink_res, "unlink");

	// Cleanup
	free(cwd);
}

void displayFile(char *filename)
{
	char *cat_buffer = malloc(sizeof(char) * READ_BUF_SIZE);
	mode_t mode = (S_IRUSR | S_IRGRP | S_IROTH); 
	int cat_res, open_res, write_res, cat_len = 0;

	// Open the file, handle any errors
	open_res = syscall(SYS_open, filename, O_RDONLY, mode);
	handleError(open_res, "open");

	// Read the file into the buffer for printing, handle any
	// errors
	cat_res = syscall(SYS_read, open_res, cat_buffer, READ_BUF_SIZE);
	handleError(cat_res, "read");

	// Make the string writeable
	cat_len = strlen(cat_buffer);
	cat_buffer[cat_len] = '\n';

	// Create the writeable string and write it out, handle any errors
	write_res = syscall(SYS_write, fileno(stdout), cat_buffer, cat_len + 1);
	handleError(write_res, "write");

	// Cleanup
	free(cat_buffer);
	close(open_res);
}

void one_arg_wrapper(char *token, char *function)
{
	// Need the delimiter here as well, argcount keeps track
	// of how many args we have so if we get more than the
	// correct amount we can break out
	const char *delimiter = " \t\n\f\r\v";
	char *arg1 = malloc(sizeof(char) * BUF_SIZE);
	int argcount = 0;

	while (token != NULL && argcount < 2)
	{
		// Handle a control char, break out when we reach one
		if (strcmp(token, ";") == 0)
		{
			break;
		}
		// One of the tokens is the function name... skip it
		if (strcmp(token, function) == 0)
		{
			token = strtok(NULL, delimiter);
			argcount++;
			continue;
		}

		strcpy(arg1, token);
		argcount++;
	}

	// Handle all the function calls
	if (strcmp(function, "mkdir") == 0 )
	{
		makeDir(arg1);
	}
	else if (strcmp(function, "cat") == 0)
	{
		displayFile(arg1);
	}
	else if (strcmp(function, "rm") == 0)
	{
		deleteFile(arg1);
	}
	else if (strcmp(function, "cd") == 0)
	{
		changeDir(arg1);
	}

	free(arg1);
}

void two_arg_wrapper(char *token, char *function)
{
	// Need the delimiter here as well, argcount keeps track
	// of how many args we have so if we get more than the
	// correct amount we can break out
	const char *delimiter = " \t\n\f\r\v";
	char *arg1 = malloc(sizeof(char) * BUF_SIZE);
	char *arg2 = malloc(sizeof(char) * BUF_SIZE);
	int argcount = 0;

	while (token != NULL && argcount < 4)
	{
		// Handle a control char, break out when we reach one
		if (strcmp(token, ";") == 0)
		{
			break;
		}
		// One of the tokens is the function name... skip it
		if (strcmp(token, function) == 0)
		{
			token = strtok(NULL, delimiter);
			argcount++;
			continue;
		}

		if (token && (strlen(arg1) == 0))
		{
			strcpy(arg1, token);
			token = strtok(NULL, delimiter);
			argcount++;
			continue;
		}

		strcpy(arg2, token);
		argcount++;
	}

	// Handle all the function calls
	if (strcmp(function, "cp") == 0 )
	{
		copyFile(arg1, arg2);
	}
	else if (strcmp(function, "mv") == 0)
	{
		moveFile(arg1, arg2);
	}

	// Cleanup
	free(arg1);
	free(arg2);
}

int main(int argc, char *argv[]) 
{
	setbuf(stdout, NULL);

	// Delimiter & token pointer to be used by strotok()
	const char *delimiter = " \t\n\f\r\v";
	char *token;

	// The in / out streams used for writing, by default going
	// to be stdin and stdout
	FILE *instream;
	FILE *outstream;

	// The variables used for getline() calls
	int changed = 0;
	char *line  = 0;
	size_t len  = 0;
	ssize_t nread;

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

		// Exit successfully if we get an exit command
		if (token != NULL) 
		{
			if (strcmp(token, "exit") == 0) 
			{
				fprintf(outstream, "\n");
				break;
			}
		}
		// Do nothing if we get empty input
		else
		{
			continue;
		}

		// Given output has a newline before displaying the tokens
		printf("\n");
		while (token != NULL) 
		{
			// Carry on if we get a semicolon in the wild
			if (strcmp(token, ";") == 0)
			{
				token = strtok(NULL, delimiter);
				continue;
			}

			// Handle "ls"
			else if (strcmp(token, "ls") == 0)
			{
				listDir();
			}

			// Handle "pwd"
			else if (strcmp(token, "pwd") == 0) 
			{
				showCurrentDir();
			}

			// Handle "mkdir"
			else if (strcmp(token, "mkdir") == 0)
			{
				one_arg_wrapper(token, "mkdir");
			}

			// Handle "cd"
			else if (strcmp(token, "cd") == 0)
			{
				one_arg_wrapper(token, "cd");
			}

			// Handle "rm"
			else if (strcmp(token, "rm") == 0)
			{
				one_arg_wrapper(token, "rm");
			}

			// Handle "cat"
			else if (strcmp(token, "cat") == 0)
			{
				one_arg_wrapper(token, "cat");
			}

			// Handle "cp"
			else if (strcmp(token, "cp") == 0)
			{
				two_arg_wrapper(token, "cp");
			}

			// Handle "mv"
			else if (strcmp(token, "mv") == 0)
			{
				two_arg_wrapper(token, "mv");
			}

			// Default case
			else
			{
				fprintf(stderr, "Unrecognized command: %s\n", token);
			}
			
			// Clean up
			token = strtok(NULL, delimiter);
		}
	}
	
	// Cleanup
	free(line);
	if (changed)
	{
		fclose(instream);
		system("perl -pi -e 'chomp if eof' pseudoshell_output.txt");
		fclose(outstream);
	}

	return EXIT_SUCCESS;
} 