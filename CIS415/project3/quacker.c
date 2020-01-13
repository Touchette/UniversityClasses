
/*
 * Description: Contains everything related to the topic queue for project
 * 3
 *
 * Author: Natalie Letz #951463883
 *
 * Date: 2019-12-18 to 2019-12-19
 *
 * Notes: A lot of methods in this file are modified from the ones given
 * in pub-sub-circular.c; I made liberal edits to the file. However, it
 * was used as a skeleton for many methods and was simply expanded upon.
 */

#include "almightyheader.h"

// Method taken from:
// 		https://www.rosettacode.org/wiki/Strip_a_set_of_characters_from_a_string#C
// in order to be able to open files when surrounded by quotes
char *strip_chars(const char *string, const char *chars)
{
  char * newstr = malloc(strlen(string) + 1);
  int counter = 0;

  for ( ; *string; string++) {
    if (!strchr(chars, *string)) {
      newstr[ counter ] = *string;
      ++ counter;
    }
  }

  newstr[counter] = 0;
  return newstr;
}

// Method taken from pub-sub-circular.c on Canvas; modified to
// more stuff fitting with project instructions and only used
// in parts 1 & 2
void initialize()
{
    int i;

    // Have to reset numTopics to 0 for the tests for parts 1 & 2,
    // if it's not reset then part 2 will think there's 20 topics
    numTopics = 0;
    // Create the topicQueues
    for (i=0; i<MAXTOPICS; ++i)
    {
        topicQueues[i].count = 0; // # entries in queue now
        topicQueues[i].head = 0; // head index
        topicQueues[i].tail = 0; // tail index
        topicQueues[i].inserted = 0; // # entries inserted in the queue overall
        topicQueues[i].length = MAXENTRIES; // length of the "entries" array
        strcpy(topicQueues[i].name, "FakeQueue");
        topicQueues[i].entries = (topicEntry *) malloc(sizeof(topicEntry) * MAXENTRIES);
        numTopics++;
    }

    // Create the buffer mutex
    for (i=0; i<MAXTOPICS; ++i)
        pthread_mutex_init(&(mutex[i]), NULL);

    pthread_attr_init(&attr);
}

// Method taken from pub-sub-circular.c on Canvas and modified to fit
// with the project instructions
int enqueue(int queueId, topicEntry *entry)
{
	// Lock the enqueue method to ensure thread-safety
	pthread_mutex_lock(&(mutex[queueId]));

	if (queueId > MAXTOPICS || queueId < 0)
	{
		pthread_mutex_unlock(&(mutex[queueId]));
		return -1;
	}

	topicQueue *currQueue = &(topicQueues[queueId]);

	// Topic queue is full, make sure to also unlock the method
	// prior to returning
	if (currQueue->count == MAXENTRIES || currQueue->length == 0)
	{
		pthread_mutex_unlock(&(mutex[queueId]));
		return -1;
	}

	topicEntry *currHead = &(currQueue->entries[currQueue->head]);
	currQueue->head = (currQueue->head + 1) % currQueue->length;

	// Go down the list of things to update in the topicEntry
	// Ones from pub-sub-circular.c
	currHead->entryNum = (currQueue->count) + 1; // new entry's number is count+1
	currQueue->count++;
	currQueue->inserted++;

	// New ones for topicEntry struct
	gettimeofday(&currHead->timestamp, NULL); // the timestamp according to manpage
	currHead->pubID = entry->pubID; // pubID is the given entry's ID
	strcpy(currHead->photoURL, entry->photoURL); // the URL is the entry's URL
	strcpy(currHead->photoCaption, entry->photoCaption); // the caption is the entry's

	// Unlock the enqueue method at the end
	pthread_mutex_unlock(&(mutex[queueId]));

	return 0;
}

// Brand new method according to instructions
int getEntry(int queueId, int lastEntry, topicEntry *emptyTopic)
{
	// Lock the getEntry method to ensure thread-safety
	pthread_mutex_lock(&(mutex[queueId]));

	if (queueId > MAXTOPICS || queueId < 0)
	{
		pthread_mutex_unlock(&(mutex[queueId]));
		return -1;
	}

	int i, currTopic;
	topicQueue *currQueue = &(topicQueues[queueId]);

	// Case 1: topic queue is empty, make sure to unlock and return
	// 0 as per the instructions
	if (currQueue->count == 0)
	{
		pthread_mutex_unlock(&(mutex[queueId]));
		return 0;
	}

	// Case 2 & Case 3ii - we always check if the entry has been
	// destroyed from our dequeue method via checking for negative
	// values of pubID
	for (i=0; i<currQueue->length; ++i)
	{
		// Numbers keep increasing so can't just use 'i' as our
		// indexing variable, modulo helps
		currTopic = (currQueue->tail + i) % currQueue->length;

		// Case 2: the lastEntry+1 entry is in the queue, so we can just
		// grab it and there is no need for the subscriber to update its
		// lastEntry number so we can just return 1
		if (currQueue->entries[currTopic].entryNum == (lastEntry+1) &&
			currQueue->entries[currTopic].pubID >= 0)
		{
			memcpy(emptyTopic, &currQueue->entries[currTopic], sizeof(topicEntry));
			pthread_mutex_unlock(&(mutex[queueId]));
			return 1;
		}
		// Case 3ii: the lastEntry+1 entry is not in the queue, but a higher
		// number is so we can just grab that one instead and update the
		// subscriber's lastEntry number
		else if (currQueue->entries[currTopic].entryNum > (lastEntry+1) &&
				 currQueue->entries[currTopic].pubID >= 0)
		{
			memcpy(emptyTopic, &currQueue->entries[currTopic], sizeof(topicEntry));
			pthread_mutex_unlock(&(mutex[queueId]));
			return currQueue->entries[currTopic].entryNum;
		}
	}

	// Unlock the getEntry method at the end
	pthread_mutex_unlock(&(mutex[queueId]));

	// Case 3i: the lastEntry+1 entry is not in the queue, and all
	// entries are of a lower number, the queue was basically empty
	return 0;
}

// Method taken from pub-sub-circular.c on Canvas and modified to fit
// with the project instructions
int dequeue(int queueId)
{
	// Lock the dequeue method to ensure thread-safety
	pthread_mutex_lock(&(mutex[queueId]));

	if (queueId > MAXTOPICS || queueId < 0)
	{
		pthread_mutex_unlock(&(mutex[queueId]));
		return -1;
	}

	topicQueue *currQueue = &(topicQueues[queueId]);

	// Topic queue is empty, make sure to also unlock the method
	// prior to returning
	if (currQueue->count == 0)
	{
		pthread_mutex_unlock(&(mutex[queueId]));
		return -1;
	}

	topicEntry currTail = currQueue->entries[currQueue->tail];

	struct timeval currTime; gettimeofday(&currTime, NULL);
	if ((difftime(currTime.tv_sec,
				 currTail.timestamp.tv_sec)) >= (double) delta)
	{
		// Destroy the current tail, reduce our total count in the
		// queue by one, and set the tail to be 1 higher than it was.
		// Ensure that getEntry doesn't grab one of these destroyed
		// topicEntries by setting its pubID to a negative number.
		memset(&currTail, 0, sizeof(topicEntry));
		// currTail.pubID = -1;
		currQueue->count--;
		currQueue->tail = (currQueue->tail + 1) % currQueue->length;
	}


	// Unlock the dequeue method at the end
	pthread_mutex_unlock(&(mutex[queueId]));

	return 0;
}

// This was taken from pub-sub-circular.c on Canvas and modified to fit
// with project instructions. Liberal use of Piazza post @216 was used
// to figure out how to structure the locking, waiting, and executing
void * publisher(void *args)
{
	int i, threadId, tries, queueId;
	threadId = ((threadargs *) args)->id;
	proxyThread *currPub = &(pubs[threadId]);
	topicEntry entry; entry.pubID = threadId;
	FILE *commandFile;

	// Only does the execution of all threads when testing part 2,
	// which is the purpose of that test. Everything it does is
	// "fake" in some sense
	if (part2)
	{
		tries = 5;
		while (tries-- > 0)
		{
			pthread_mutex_lock(&(globalMutex));

			pthread_cond_wait(&(mutexCondition), &(globalMutex));

			pthread_mutex_unlock(&(globalMutex));

			for (i=0; i<MAXTOPICS; ++i)
			{
				sprintf(entry.photoURL, "idk");
				sprintf(entry.photoCaption, "d");
				if (enqueue(i, &entry) == 0)
				{
					printf("Publisher %d - executed enqueue(%d, %s)\n",
						threadId, i, entry.photoCaption);
					currPub->status = FREE;
					proxyCount--;
					return NULL;
				}
			}

			sleep(1);
		}
	}

	// Skip all the rest if we're just testing part 3
	if (part3)
	{
		printf("Proxy thread %d - type: Publisher\n", threadId);
		return NULL;
	}

	// If we're testing part 4, we need to open up files and stuff
	// to execute the commands inside
	if (part4)
	{
		commandFile = fopen(strip_chars(currPub->filename, "\""), "r");
		if (commandFile == NULL)
		{
			fprintf(stderr, "Could not open publisher command file.\n");
			currPub->status = FREE;
			return NULL;
		}

		char *token;
		char *tokens[4];
		char *saveString;
		char *line;
		size_t len = 0;
		ssize_t nread = 0;

		while ((nread = getline(&line, &len, commandFile)) != -1)
		{
			// Break up the line to get the commands, max length of a command
			// will be 5. In Piazza post @230, Jared warns against using strtok
			// because it is not thread-safe, so I use strtok_r here.
			token = strtok_r(line, delimiter, &saveString);
			for (i=0; i<4; ++i)
			{
				tokens[i] = token;
				token = strtok_r(NULL, delimiter, &saveString);
			}

			if (strcmp(tokens[0], "put") == 0)
			{
				queueId = atoi(tokens[1]);
				strcpy(entry.photoURL, tokens[2]);
				strcpy(entry.photoCaption, tokens[3]);
			}
			else if (strcmp(tokens[0], "sleep") == 0)
			{
				int time = atoi(tokens[1]);
				sleep(time > 1000 ? (time / 1000) : (time / 100));
				continue;
			}
			else if (strcmp(tokens[0], "stop") == 0)
			{
				printf("Publisher %d stopping by command.\n", threadId);
				break;
			}

			tries = 5;
			while (tries-- > 0)
			{
				pthread_cond_wait(&(mutexCondition), &(globalMutex));

				pthread_mutex_lock(&(globalMutex));
				if (enqueue(queueId, &entry) == 0)
				{
					printf("Publisher %d - executed enqueue(%d, %s)\n",
						threadId, queueId, entry.photoCaption);
					pthread_mutex_unlock(&(globalMutex));
					break;
				}

				pthread_mutex_unlock(&(globalMutex));
			}
		}
	}

	currPub->status = FREE;
	proxyCount--;
	return NULL;
}

// This was taken from pub-sub-circular.c on Canvas and modified to fit
// with project instructions. Liberal use of Piazza post @216 was used
// to figure out how to structure the locking, waiting, and executing
void * subscriber(void *args)
{
	int	i, threadId, tries, queueId;
	int lastEntry = 0;
	threadId = ((threadargs *) args)->id;
	proxyThread *currSub = &(subs[threadId]);
	topicEntry entry;
	FILE *commandFile;

	if (part2)
	{
		tries = 5;
		while (tries-- > 0)
		{
			pthread_mutex_lock(&(globalMutex));

			pthread_cond_wait(&(mutexCondition), &(globalMutex));

			pthread_mutex_unlock(&(globalMutex));
			for (i=0; i<MAXTOPICS; ++i)
			{
				if (getEntry(i, 0, &entry) > lastEntry)
				{
					printf("Subscriber %d - executed getEntry(%d, 0, &entry)\n", threadId, i);
					currSub->status = FREE;
					proxyCount--;
					return NULL;
				}
			}

			sleep(1);
		}
	}

	if (part3)
	{
		printf("Proxy thread %d - type: Subscriber\n", threadId);
		return NULL;
	}

	// If we're testing part 4, we need to open up files and stuff
	// to execute the commands inside
	if (part4)
	{
		commandFile = fopen(strip_chars(currSub->filename, "\""), "r");
		if (commandFile == NULL)
		{
			fprintf(stderr, "Could not open subscriber command file.\n");
			currSub->status = FREE;
			return NULL;
		}

		char *token;
		char *tokens[2];
		char *saveString;
		char *line;
		size_t len = 0;
		ssize_t nread = 0;

		while ((nread = getline(&line, &len, commandFile)) != -1)
		{
			// Break up the line to get the commands, max length of a command
			// will be 5. In Piazza post @230, Jared warns against using strtok
			// because it is not thread-safe, so I use strtok_r here.
			token = strtok_r(line, delimiter, &saveString);
			for (i=0; i<2; ++i)
			{
				tokens[i] = token;
				token = strtok_r(NULL, delimiter, &saveString);
			}

			if (strcmp(tokens[0], "get") == 0)
			{
				queueId = atoi(tokens[1]);
			}
			else if (strcmp(tokens[0], "sleep") == 0)
			{
				int time = atoi(tokens[1]);
				sleep(time > 1000 ? (time / 1000) : (time / 100));
				continue;
			}
			else if (strcmp(tokens[0], "stop") == 0)
			{
				printf("Subscriber %d stopping by command.\n", threadId);
				break;
			}

			tries = 5;
			while (tries-- > 0)
			{
				pthread_cond_wait(&(mutexCondition), &(globalMutex));

				pthread_mutex_lock(&(globalMutex));
				int x = getEntry(queueId, lastEntry, &entry);
				if (x >= lastEntry)
				{
					printf("Subscriber %d - executed getEntry(%d, %d, &entry)\n", threadId, lastEntry, queueId);
					pthread_mutex_unlock(&(globalMutex));
					break;
				}

				pthread_mutex_unlock(&(globalMutex));
			}
		}
	}

	currSub->status = FREE;
	proxyCount--;
	return NULL;
}

// Brand new method based on publisher() and subscriber(). This one is
// a lot simpler though, as it just goes around cleaning up queues as
// it can get the locks, the delta time is long enough (as is laid out
// in dequeue()), and there are still proxyThreads left
void * topicCleanup(void *args)
{
	int	i;
	proxyThread *topicCleaner = (proxyThread *) args;

	if (part3)
	{
		topicCleaner->status = FREE;
		return NULL;
	}

	while (proxyCount > 0)
	{
		for (i=0; i<MAXTOPICS; ++i)
		{
			if (topicQueues[i].length > 0)
			{
				dequeue(i);
			}
		}
	}

	printf("No more proxy threads - cleanupThread exiting\n");
	topicCleaner->status = FREE;
	return NULL;
}

// The command for creating a new topic queue:
//		create topic <ID> <"Name"> <Length>
int createTopic(int id, char *name, int length)
{
	// Make sure the in put is valid
	if (length < 0 || length >= MAXENTRIES || id < 0 || id > MAXTOPICS)
	{
		fprintf(stderr, "Create topic: invalid length or id.\n");
		return -1;
	}

	// Initialize the topic we were given
	topicQueue *currTopic = &(topicQueues[id]);

    currTopic->count = 0; // # entries in queue now
    currTopic->head = 0; // head index
    currTopic->tail = 0; // tail index
    currTopic->inserted = 0; // # entries inserted in the queue overall
    currTopic->length = length; // length of the "entries" array
    strcpy(currTopic->name, name); // name of the queue
    currTopic->entries = (topicEntry *) malloc(sizeof(topicEntry) * length);

	pthread_mutex_init(&(mutex[id]), NULL); // initialize the mutex at location id

	numTopics++;

    return 0;
}

// The command for querying all the topic lengths:
//		query topics
int queryTopics()
{
	int i;

	for (i=0; i<MAXTOPICS; ++i)
	{
		topicQueue currTopic = topicQueues[i];
		if (currTopic.length > 0)
		{
			printf("Topic %d is length %d\n", i, currTopic.length);
		}
	}

	return 0;
}

// The command for adding a publisher thread:
//		add publisher <filename>
int addPublisher(char *filename)
{
	if (proxyCount >= MAXPROXIES)
	{
		fprintf(stderr, "Maximum number of proxy threads allocated.\n");
		return -1;
	}

	// Initialize the latest free thread
	proxyThread *currThread = &(pubs[proxyCount]);

	currThread->id = proxyCount;
	currThread->status = RUNNING;
	strcpy(currThread->filename, filename);

	proxyCount++;

	return 0;
}

// The command for querying all publisher's command files:
//		query publishers
int queryPublishers()
{
	int i;

	for (i=0; i<MAXPROXIES; ++i)
	{
		proxyThread currPub = pubs[i];
		if (currPub.status == RUNNING)
		{
			printf("Publisher %d has command file %s\n", i, currPub.filename);
		}
	}

	return 0;
}

// The command for adding a subscriber thread:
//		add subscriber <filename>
int addSubscriber(char *filename)
{
	if (proxyCount >= MAXPROXIES)
	{
		fprintf(stderr, "Maximum number of proxy threads allocated.\n");
		return -1;
	}

	// Initialize the latest free thread
	proxyThread *currThread = &(subs[proxyCount]);

	currThread->id = proxyCount;
	currThread->status = RUNNING;
	strcpy(currThread->filename, filename);

	proxyCount++;

	return 0;
}

// The command for querying all subscriber's command files:
//		query subscribers
int querySubscribers()
{
	int i;

	for (i=0; i<MAXPROXIES; ++i)
	{
		proxyThread currSub = subs[i];
		if (currSub.status == RUNNING)
		{
			printf("Subscriber %d has command file %s\n", i, currSub.filename);
		}
	}

	return 0;
}

// The command for changing the delta for topicCleanupThread:
//		delta <newVal>
int changeDelta(int newVal)
{
	if (newVal <= 0)
	{
		fprintf(stderr, "Delta: new value must be non-negative.\n");
		return -1;
	}

	delta = newVal;

	printf("Delta value has been updated to %d (integer)\n", delta);

	return 0;
}

// The command for starting all the created threads:
//		start
int start()
{
	int i;

    pthread_create(&topicCleanupThread.thread, &attr, &topicCleanup, &topicCleanupThread);
    topicCleanupThread.status = RUNNING;

    // Initialize all the threads for testing
    for (i=0; i<MAXPROXIES; ++i)
    {
        // Create MAXPROXIES publisher threads
	    pubargs[i].id = i;
        if (pubs[i].status == RUNNING)
        {
			pthread_create(&(pubs[i].thread), &attr, &publisher, (void *) &pubargs[i]);
        }

        // Create subscriber threads
		subargs[i].id = i;
		if (subs[i].status == RUNNING)
		{
        	pthread_create(&(subs[i].thread), &attr, &subscriber, (void *) &subargs[i]);
		}
    }

	pthread_mutex_init(&(globalMutex), NULL);
    while (topicCleanupThread.status != FREE)
    {
		pthread_mutex_lock(&(globalMutex));

		pthread_cond_broadcast(&(mutexCondition));

		pthread_mutex_unlock(&(globalMutex));
	}

	printf("The entered commands have finished executing.\n");
	return 0;
}

// This is taken from my project 1 terminal emulator, modified
// to use strncmp so that I don't have to use strtok in main(),
// I can just check the entire line against a command!
char * checkCommand(char *cmd)
{
	if (cmd == NULL)
		return 0;
	else if (strncmp(cmd, "create topic", strlen("create topic")) == 0)
		return "create topic";
	else if (strncmp(cmd, "query topics", strlen("query topics")) == 0)
		return "query topics";
	else if (strncmp(cmd, "add publisher", strlen("add publisher")) == 0)
		return "add publisher";
	else if (strncmp(cmd, "query publishers", strlen("query publishers")) == 0)
		return "query publishers";
	else if (strncmp(cmd, "add subscriber", strlen("add subscriber")) == 0)
		return "add subscriber";
	else if (strncmp(cmd, "query subscribers", strlen("query subscribers")) == 0)
		return "query subscribers";
	else if (strncmp(cmd, "delta", strlen("delta")) == 0)
		return "delta";
	else if (strncmp(cmd, "start", strlen("start")) == 0)
		return "start";
	else
		return 0;
}

// This is taken from my project 1 terminal emulator, modified
// to use strcmp and setup such that the methods themselves get
// their own arguments
void callFunction(char *cmd, char *line)
{
	int i;
	char *token;
	char *tokens[5];

	// Break up the line to get the commands, max length of a command
	// will be 5. In Piazza post @230, Jared warns against using strtok
	// because it is not thread-safe, however this method is not called
	// by multiple threads to begin with.
	token = strtok(line, delimiter);
	for (i=0; i<5; ++i)
	{
		tokens[i] = token;
		token = strtok(NULL, delimiter);
	}

	if (strcmp(cmd, "create topic") == 0)
	{
		if (tokens[2] == NULL ||  tokens[3] == NULL || tokens[4] == NULL)
		{
			fprintf(stderr, "Create topic: missing or invalid argument.\n");
			return;
		}
		createTopic(atoi(tokens[2]), tokens[3], atoi(tokens[4]));
	}
	else if (strcmp(cmd, "query topics") == 0)
	{
		queryTopics();
	}
	else if (strcmp(cmd, "add publisher") == 0)
	{
		if (tokens[2] == NULL)
		{
			fprintf(stderr, "Add publisher: missing or invalid filename.\n");
			return;
		}
		addPublisher(tokens[2]);
	}
	else if (strcmp(cmd, "query publishers") == 0)
	{
		queryPublishers();
	}
	else if (strcmp(cmd, "add subscriber") == 0)
	{
		if (tokens[2] == NULL)
		{
			fprintf(stderr, "Add subscriber: missing or invalid filename.\n");
			return;
		}
		addSubscriber(tokens[2]);
	}
	else if (strcmp(cmd, "query subscribers") == 0)
	{
		querySubscribers();
	}
	else if (strcmp(cmd, "delta") == 0)
	{
		if (tokens[1] == NULL)
		{
			fprintf(stderr, "Delta: invalid delta.\n");
			return;
		}
		changeDelta(atoi(tokens[1]));
	}
	else if (strcmp(cmd, "start") == 0)
	{
		start();
	}
}

int main(int argc, char *argv[])
{
	int i;
	char line[128];
	size_t len = 0;
	ssize_t nread = 0;
	char *command;

	// Part 1 and 2 tests
	if (argc > 1 && (strcmp(argv[1], "-part12tests") == 0))
	{
		// Part one tests
		printf(".:*~*:._.:*~* Part One Tests *~*:._.:*~*:.\n");

		topicEntry entryPartOne;
		entryPartOne.pubID = rand();
		sprintf(entryPartOne.photoURL, "entryPartOneURL\n");
		sprintf(entryPartOne.photoCaption, "entryPartOneCaption\n");

		initialize();

		printf("Enqueue result was: %d (0 is success)\n", enqueue(0, &entryPartOne));
		printf("getEntry result was: %d (1 is success)\n", getEntry(0, 0, &entryPartOne));
		sleep(sleepyTime);
		printf("Dequeue result was: %d (0 is success)\n", dequeue(0));
		printf("Size of queue0 is: %d\n", topicQueues[0].count);

		sleep(sleepyTime/2);

		// Part two tests
		printf("\n.:*~*:._.:*~* Part Two Tests *~*:._.:*~*:.\n");

		part2 = 1;

		initialize();

	    // Initialize all the threads for testing
	    for (i=0; i<MAXPROXIES; ++i)
	    {
	        // Create MAXPROXIES publisher threads, put them in the table
	        // representing the threadpool
	        pubargs[i].id = i;
	        pthread_create(&(pubs[i].thread), &attr, &publisher, (void *) &pubargs[i]);
	        pubs[i].status = RUNNING;
	        proxyCount++;

	        // Create MAXPROXIES subscriber threads, put them in the table
	        // representing the threadpool
	        subargs[i].id = i;
	        pthread_create(&(subs[i].thread), &attr, &subscriber, (void *) &subargs[i]);
	        subs[i].status = RUNNING;
	        proxyCount++;
	    }

	    pthread_create(&topicCleanupThread.thread, &attr, &topicCleanup, (void *) &topicCleanupThread);
	    topicCleanupThread.status = RUNNING;

	    while (topicCleanupThread.status != FREE)
	    {
			pthread_mutex_lock(&globalMutex);

			pthread_cond_broadcast(&mutexCondition);

			pthread_mutex_unlock(&globalMutex);

			sleep(sleepyTime/2);
	    }

		return EXIT_SUCCESS;
	}

	// Part 3 tests
	if (argc > 1 && (strcmp(argv[1], "-part3tests") == 0))
	{
		printf("\n.:*~*:._.:*~* Part Three Tests *~*:._.:*~*:.\n");

		part3 = 1;

		// https://stackoverflow.com/questions/40038538/how-does-scanf-n-str-work-in-c-programming
		while (scanf(" %127[^\n]", line) > 0)
		{
	        if (strlen(line) == 0)
	            continue;

			if ((command = checkCommand(line)))
	        {
	            callFunction(command, line);
	        }
	        else if (strcmp(line, "exit") == 0)
	        {
	        	break;
	        }
	        else
	        {
	        	fprintf(stderr, "Unsupported command: %s\n", line);
	        }
	    }

	    return EXIT_SUCCESS;
	}

	// Part 4 tests
	if (argc > 1 && (strcmp(argv[1], "-part4tests") == 0))
	{
		printf("\n.:*~*:._.:*~* Part Four Tests *~*:._.:*~*:.\n");

		part4 = 1;

		char *lineptr = 0;
		FILE *configFile = fopen("config.txt", "r");

		// This is basically entirely taken from my project 1 main function
		while ((nread = getline(&lineptr, &len, configFile) != -1))
		{
	        if (strlen(lineptr) == 0)
	            continue;

			if ((command = checkCommand(lineptr)))
	        {
	            callFunction(command, lineptr);
	        }
	        else if (strcmp(lineptr, "exit") == 0)
	        {
	        	break;
	        }
	        else
	        {
	        	fprintf(stderr, "Unsupported command: %s\n", lineptr);
	        }
	    }

	    free(lineptr);
	    return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}
