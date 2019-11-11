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
int totalProcCount, totalRunningProc = 0;
int run, idx = 0;

// Part 4 Functions
int stringStartsWith(const char *a, const char *b);
void prettyPrinter();

// Part 3 Functions
int checkProcessStatus(pid_t pid);
void sigusr1(int signal);
void sigalrm(int signal);
void sigchld(int signal);

// Part 1 & 2 Functions
void cleanParams(char **params);
void mainCleaner(char *command, char** params);

#endif
