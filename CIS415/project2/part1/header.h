#ifndef HEADER_H
#define HEADER_H

#include <sys/syscall.h>
#include <libgen.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <wait.h>
#include <time.h>

#define BUF_SIZE 1024

pid_t pids[BUF_SIZE] = { 0 };

// Part 1 & 2 Functions
void cleanParams(char **params);
void mainCleaner(char *command, char** params);

#endif
