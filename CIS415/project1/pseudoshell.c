/*
 * Description: a very basic bash emulator that can simulate a few
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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#define AT_FDCWD -100
#define BUF_SIZE 1024


// Used for the ls_wrapper function for the getdents syscall
// to work for printing... no idea what's going on tho
struct linux_dirent
{
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

int handle_error(int err, const char *callname) 
{
	// Get the errno so I can reference the documentation
	fprintf(stderr, "Error in %s: %d. Problem:\n\t", callname, err);
	// Get the error output that C provides for more clues
	perror(callname);

	return 1;
}

int ls_wrapper(int dirfd, const char *pathname, FILE *dest) 
{
	char *buffer = malloc(sizeof(char) * BUF_SIZE);
	int openat_res, getdents_res;
	struct linux_dirent *d;
	char d_type;

	// Open the filepath
	openat_res = syscall(SYS_openat, dirfd, ".", O_DIRECTORY);

	// Handle errors if there are any
	if (openat_res == -1) 
	{
		handle_error(errno, "openat");
		return openat_res;
	}

	do 
	{
		// Make sure to check for errors at the start of every
		// loop, it can't be -1 on the first loop so this is fine
		if (getdents_res == -1) 
		{
			handle_error(errno, "getdents");
			return getdents_res;
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

			// Printing the names
			if (d_type != DT_DIR)
			{
				fprintf(dest, "%s ", d->d_name);
			}
			else
			{
				// Make sure not to print the current directory or the parent directory
				if ((strcmp(d->d_name, ".") != 0) && (strcmp(d->d_name, "..") != 0))
				{
					fprintf(dest, "\e[1m%s\e[0m ", d->d_name); 
				}
			}

			bpos += d->d_reclen;
		}
	} while (getdents_res != 0);
	
	fprintf(dest, "\n");

	// Cleanup
	free(buffer);
	return 0;
}

int pwd_wrapper(FILE *dest)
{
	char *cwd_buffer = malloc(sizeof(char) * BUF_SIZE);
	int getcwd_res, write_res, buffer_len;

	// Get the string that is the current directory name
	getcwd_res = syscall(SYS_getcwd, cwd_buffer, BUF_SIZE);
	buffer_len = strlen(cwd_buffer);
	cwd_buffer[buffer_len] = '\n';

	// Write it out to the file
	write_res = syscall(SYS_write, fileno(dest), cwd_buffer, buffer_len + 1);

	// Error handling
	if (getcwd_res == -1)
	{
		handle_error(errno, "getcwd");
	}
	if (write_res == -1) 
	{
		handle_error(errno, "write");
	}

	// Cleanup
	free(cwd_buffer);
	return 0;
}

int cd_wrapper(const char *path, FILE *dest)
{
	char *cwd = malloc(sizeof(char) * BUF_SIZE);
	int chdir_res, write_res, cwd_len;

	// Constructing the relative path if we need to
	if (path[0] != '/')
	{
		cwd = getcwd(cwd, BUF_SIZE);
		strcat(cwd, "/");
		strcat(cwd, path);
		chdir_res = syscall(SYS_chdir, cwd);
		cwd_len = strlen(cwd);
	}
	// Otherwise we were given an absolute path, do it
	// directly
	else
	{
		chdir_res = syscall(SYS_chdir, path);
		cwd_len = strlen(path);
	}
	
	// Write the output (the new directory we are in)
	cwd[cwd_len] = '\n';
	write_res = syscall(SYS_write, fileno(dest), cwd, cwd_len + 1);

	// Error handling
	if (chdir_res == -1)
	{
		handle_error(errno, "chdir");
	}
	if (write_res == -1) 
	{
		handle_error(errno, "write");
	}

	// Cleanup
	free(cwd);
	return 0;
}

int main(int argc, char *argv[]) 
{
	setbuf(stdout, NULL);

	/* Main function variables & allocation of memory for input */
	// Delimiter & token pointer to be used by strotok()
	const char *delimiter = " \t\n\f\r\v";
	char *token;

	// The in / out streams used for writing, by default going
	// to be stdin and stdout
	FILE *instream;
	FILE *outstream;

	// The variables used for getline() calls
	char *line = 0;
	size_t len = 0;
	ssize_t nread;

	// Setting up the streams
	instream  = stdin;
	outstream = stdout;
	if (argc > 1) 
	{
		instream = fopen(argv[1], "r");
		outstream = fopen("pseudoshell_output.txt", "w");
		if (instream == NULL || outstream == NULL) 
		{
			perror("fopen");
			exit(1);
		}
	}

	/* Main run loop */
	while (((outstream == stdout) ? printf(">>> ") : 1) 
		&& (nread = getline(&line, &len, instream)) != -1) 
	{
		// Tokenize the input string
		token = strtok(line, delimiter);

		// Exit successfully if we get an exit command, do nothing if we
		// get empty input
		if (token != NULL) 
		{
			if (strcmp(token, "exit") == 0) 
			{
				fprintf(outstream, "\n");
				break;
			}
		} 
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
				ls_wrapper(AT_FDCWD, ".", outstream);
			}

			// Handle "pwd"
			else if (strcmp(token, "pwd") == 0) 
			{
				pwd_wrapper(outstream);
			}

			// Handle "cd"
			else if (strcmp(token, "cd") == 0)
			{
				int argcount = 0;
				while (token != NULL && argcount < 2)
				{
					if (strcmp(token, ";") == 0)
					{
						break;
					}
					if (strcmp(token, "cd") == 0)
					{
						token = strtok(NULL, delimiter);
						argcount++;
						continue;
					}

					cd_wrapper(token, outstream);
					argcount++;
				}
			}
			
			// Clean up
			token = strtok(NULL, delimiter);
		}
	}
	
	/* Memory cleanup & closing files */
	free(line);
	if (instream != stdin)
	{
		fclose(instream);
		fclose(outstream);
	}

	return 0;
} 