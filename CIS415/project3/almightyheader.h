
/*
 * Description: The header file I use for basically everything in this
 * project
 *
 * Author: Natalie Letz #951463883
 *
 * Date: 2019-12-18 to 2019-12-19
 *
 * Notes: Many items in this file were either taken from pub-sub-circular.c
 * or slightly modified from the same file in order to fit with the handout
 * given on Canvas. For example, pub-sub-circular.c implemented "entry" &
 * "queue", here I typedef them and rename them appropriate to the project
 * description. Furthermore, the definitions at the top of the file have
 * either been renamed or removed because of redundancy. I removed all
 * references to anything related to a "semaphore".
 */

#ifndef ALMIGHTYHEADER_H
#define ALMIGHTYHEADER_H

#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>


// +--------------------+
// | Global Definitions |
// +--------------------+

#define MAXENTRIES	  50	// maximum number of entries
#define MAXTOPICS     10	// maximum number of topic queues
#define MAXPROXIES    10	// maximum number of proxies
#define URLSIZE       80	// URL size
#define CAPSIZE       100	// caption size
#define FREE          0		// Part2: thread status is free
#define RUNNING       1		// Part2: thread status is not free

int part2 = 0; // Part 2: are we testing part 2 currently?
int part3 = 0; // Part 3: are we testing part 3 currently?
int part4 = 0; // Part 4: are we testing part 4 currently?
int proxyCount = 0; // current number of pubs and subs
int	numTopics = 0; // current number of topic queues
int running = 0; // Part 2: number of threads that are running
int	sleepyTime = 5; // sleep time for main thread
int delta = 5; // time delta for cleanup thread
// Part 2: global mutex stuff from @216 on Piazza
pthread_mutex_t globalMutex;
pthread_cond_t mutexCondition;
// Part 3: delimiter for functions to read commands with strtok()
const char *delimiter = " \t\n\f\r\v";


// +----------------------+
// | Typedef Declarations |
// |          &           |
// |   Associated Data    |
// +----------------------+

// Topic Entry struct
typedef struct
{
	int entryNum;
	struct timeval timestamp;
	int pubID;
	char photoURL[URLSIZE];
	char photoCaption[CAPSIZE];
} topicEntry;

// Circular Ring Buffer struct
typedef struct
{
	int count, head, tail, inserted, length;
	char name[64];
	topicEntry *entries;
} topicQueue;

topicQueue topicQueues[MAXTOPICS]; // topic queues
pthread_mutex_t mutex[MAXTOPICS]; // mutex locks for topic queues

// Threadargs struct to be passed as argument #4 in a
// pthread_create() call
typedef struct
{
	int	id;
} threadargs;

// Part 2: to be used by the proxy threadpools which are to
// contain:
//		- a thread,
//		- a status to tell if it is free,
//		- the thread's ID,
//		- (Part 4) the thread's command filename
typedef struct 
{
	pthread_t thread;
	int status; // default thread status is free
	int id;
	char filename[64];
} proxyThread;

threadargs pubargs[MAXPROXIES];
threadargs subargs[MAXPROXIES];

// Part 2: The proxy threadpools and the "attributes" argument for
// pthread_create()
proxyThread pubs[MAXPROXIES]; // pool for publishers
proxyThread subs[MAXPROXIES]; // pool for subscribers

proxyThread topicCleanupThread; // singular "topic cleanup thread"
threadargs topicCleanupArgs = { 1 };

pthread_attr_t attr; // thread attributes


// +---------------------+
// | Method Declarations |
// +---------------------+

// Part 1
void initialize();
int enqueue(int queueId, topicEntry *entry);
int getEntry(int queueId, int lastEntry, topicEntry *emptyTopic);
int dequeue(int queueId);

// Part 2
void * publisher(void *args);
void * subscriber(void *args);
void * topicCleanup(void *args);

// Part 3
int createTopic(int id, char *name, int length);
int queryTopics();
int addPublisher(char *filename);
int queryPublishers();
int addSubscriber(char *filename);
int querySubscribers();
int changeDelta(int newVal);
int start();

#endif
