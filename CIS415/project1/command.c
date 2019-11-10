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

/*--------------------------Struct/Enum Definitions--------------------------*/
// Used for the ls_wrapper function for the getdents syscall
// to work for printing... no idea what's going on tho
struct linux_dirent
{
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};
/*---------------------------------------------------------------------------*/

/*--------------------------Function Definitions-----------------------------*/
// My error handler that uses perror to give way more descriptive error
// printouts
int handleError(int res, const char *callname)
{
	if (res == -1)
	{
		// Get the errno so I can reference the documentation
		fprintf(stderr, "Error in %s; errno is %d.\n", callname, errno);
		perror(callname);

		return -1;
	}

	return 0;
}

// Makes absolute paths from relative paths for various system calls
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

// Free function to be used by every function for when they
// need to exit early / for cleanup
void freeStuff(void *ptr1, void *ptr2, void *ptr3, void *ptr4)
{
	free(ptr1); ptr1 = NULL;
	free(ptr2); ptr2 = NULL;
	free(ptr3); ptr3 = NULL;
	free(ptr4); ptr4 = NULL;
}

// ls
void listDir()
{
	char *buffer = malloc(sizeof(char) * BUF_SIZE);
	int openat_res, write_res, getdents_res = 0;
	struct linux_dirent *d;
	char d_type;

	// Open the filepath
	openat_res = syscall(SYS_openat, AT_FDCWD, ".", O_DIRECTORY);

	// Handle openat errors if there are any and prematurely exit
	if (handleError(openat_res, "openat") == -1)
	{
		freeStuff(buffer, NULL, NULL, NULL);
		return;
	}

	do
	{
		// Make sure to check for errors at the start of every
		// loop, it can't be -1 on the first loop so this is fine
		if (handleError(getdents_res, "getdents") == -1)
		{
			freeStuff(buffer, NULL, NULL, NULL);
			return;
		}

		// Scan the filepath for files
		getdents_res = syscall(SYS_getdents, openat_res, buffer, BUF_SIZE);

		// Print the files according to the documentation on the manpage
		// for getdents (only files, no directories)
		int bpos;
		for (bpos = 0; bpos < getdents_res;)
		{
			// ???
			d = (struct linux_dirent *) (buffer + bpos);
			d_type = *(buffer + bpos + d->d_reclen - 1);
			write_res = syscall(SYS_write,
				fileno(stdout),
				strcat(d->d_name, " "),
				strlen(d->d_name) + 1);
			handleError(write_res, "write");

			bpos += d->d_reclen;
		}
	} while (getdents_res != 0);

	// Print the final newline and check for errors one last time
	write_res = syscall(SYS_write, fileno(stdout), "\n", sizeof(char));
	if (handleError(write_res, "write") == -1)
	{
		freeStuff(buffer, NULL, NULL, NULL);
		return;
	}

	// Cleanup
	freeStuff(buffer, NULL, NULL, NULL);
}

// pwd
void showCurrentDir()
{
	char *cwd_buffer = malloc(sizeof(char) * BUF_SIZE);
	int getcwd_res, write_res, cwd_len = 0;

	// Get the string that is the current directory name and
	// handle its errors
	getcwd_res = syscall(SYS_getcwd, cwd_buffer, BUF_SIZE);
	if (handleError(getcwd_res, "getcwd") == -1)
	{
		freeStuff(cwd_buffer, NULL, NULL, NULL);
		return;
	}

	// Create the writeable string
	cwd_len = strlen(cwd_buffer);
	cwd_buffer[cwd_len] = '\n';

	// Write it out to the file and handle its errors
	write_res = syscall(SYS_write, fileno(stdout), cwd_buffer, cwd_len + 1);
	if (handleError(write_res, "write") == -1)
	{
		freeStuff(cwd_buffer, NULL, NULL, NULL);
		return;
	}

	// Cleanup
	freeStuff(cwd_buffer, NULL, NULL, NULL);
}

// mkdir
void makeDir(char *dirName)
{
	mode_t mode = (S_IRWXU | S_IRWXG | S_IRWXO);
	int mkdir_res = 0;

	// Create a folder with a mode that allows all users to read to it
	// and write to it, handle its errors
	mkdir_res = syscall(SYS_mkdir, dirName, mode);
	handleError(mkdir_res, "mkdir");
}

// cd
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
	freeStuff(cwd, NULL, NULL, NULL);
}

// cp
void copyFile(char *sourcePath, char *destinationPath)
{
	// Setting up the source path we were given as well as
	// where we're going
	char *read_buffer = malloc(sizeof(char) * READ_BUF_SIZE);
	char *sourcePath_buffer = NULL;
	char *destPath_buffer = NULL;

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
		destPath_buffer = createAbsPath(destinationPath);
	}
	// Otherwise just use it
	else
	{
		destPath_buffer = destinationPath;
	}

	destPath_buffer = strcat(destPath_buffer, destination_filename);

	// Normal stuff from other functions
	mode_t mode = 0666;
	int open_res, read_res, write_res, creat_res, read_len = 0;

	// Open the source file, handle any errors
	open_res = syscall(SYS_open, sourcePath_buffer, O_RDWR, mode);
	if (handleError(open_res, "open") == -1)
	{
		freeStuff(read_buffer, sourcePath_buffer, destPath_buffer, destination_filename);
	}

	// Read the source file into the buffer
	read_res = syscall(SYS_read, open_res, read_buffer, READ_BUF_SIZE);
	// Handle errors if there are any
	if (handleError(read_res, "rename") == -1)
	{
		freeStuff(read_buffer, sourcePath_buffer, destPath_buffer, destination_filename);
		close(open_res);
		return;
	}
	close(open_res);

	// Open the destination file
	open_res = syscall(SYS_open, destPath_buffer, (O_CREAT | O_RDWR), mode);
	// Handle errors if there are any
	if (handleError(open_res, "open") == -1)
	{
		freeStuff(read_buffer, sourcePath_buffer, destPath_buffer, destination_filename);
		return;
	}

	// Write the file into the source destination
	write_res = syscall(SYS_write, open_res, read_buffer, strlen(read_buffer));
	// Handle errors if there are any
	if (handleError(write_res, "write") == -1)
	{
		freeStuff(read_buffer, sourcePath_buffer, destPath_buffer, destination_filename);
		return;
	}
	close(open_res);

	// Cleanup
	freeStuff(read_buffer, sourcePath_buffer, destPath_buffer, destination_filename);
}

// mv
void moveFile(char *sourcePath, char *destinationPath)
{
	// All of this is same as copy basically
	char *sourcePath_buffer = NULL;
	char *destPath_buffer = NULL;
	int rename_res, getcwd_res = 0;

	// Always use abs path of source
	if (sourcePath[0] != '/')
	{
		sourcePath_buffer = createAbsPath(sourcePath);
	}
	else
	{
		sourcePath_buffer = sourcePath;
	}

	if (destinationPath[0] != '/')
	{
		destPath_buffer = createAbsPath(destinationPath);
	}
	// If we got ".", just use the current directory
	else if (strcmp(destinationPath, ".") == 0)
	{
		getcwd_res = syscall(SYS_getcwd, destPath_buffer, BUF_SIZE);
	}
	// Otherwise we got a full path, use it
	else
	{
		destPath_buffer = destinationPath;
	}

	// Handle errors if there are any
	if (handleError(getcwd_res, "getcwd") == -1)
	{
		freeStuff(sourcePath_buffer, destPath_buffer, NULL, NULL);
		return;
	}

	// Rename will actually move a file directories if it needs to...
	// ... good thing I did all the work up there to get full pathnames
	rename_res = syscall(SYS_rename, sourcePath_buffer, destPath_buffer);
	// Handle errors if there are any
	if (handleError(rename_res, "rename") == -1)
	{
		freeStuff(sourcePath_buffer, destPath_buffer, NULL, NULL);
		return;
	}

	// Cleanup
	freeStuff(sourcePath_buffer, destPath_buffer, NULL, NULL);
}

// rm
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
	freeStuff(cwd, NULL, NULL, NULL);
}

// cat
void displayFile(char *filename)
{
	char *cat_buffer = malloc(sizeof(char) * READ_BUF_SIZE);
	mode_t mode = (S_IRUSR | S_IRGRP | S_IROTH);
	int cat_res, open_res, write_res, cat_len = 0;

	// Open the file, handle any errors
	open_res = syscall(SYS_open, filename, O_RDONLY, mode);
	if (handleError(open_res, "open") == -1)
	{
		freeStuff(cat_buffer, NULL, NULL, NULL);
		return;
	}

	// Read the file into the buffer for printing, handle any
	// errors
	cat_res = syscall(SYS_read, open_res, cat_buffer, READ_BUF_SIZE);
	if (handleError(cat_res, "read") == -1)
	{
		freeStuff(cat_buffer, NULL, NULL, NULL);
		return;
	}

	// Make the string writeable
	cat_len = strlen(cat_buffer);
	cat_buffer[cat_len] = '\n';

	// Create the writeable string and write it out, handle any errors
	write_res = syscall(SYS_write, fileno(stdout), cat_buffer, cat_len + 1);
	if (handleError(write_res, "write") == -1)
	{
		freeStuff(cat_buffer, NULL, NULL, NULL);
		return;
	}

	// Cleanup
	freeStuff(cat_buffer, NULL, NULL, NULL);
	close(open_res);
}

/*---------------------------------------------------------------------------*/
