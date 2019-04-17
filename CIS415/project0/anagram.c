#include "anagram.h"
#include <stdlib.h>

// I would be insane to not use bools thanks
typedef enum { false, true } bool;

typedef struct StringList StringList;
typedef struct AnagramList AnagramList;

// Create a new string list node
StringList *MallocSList(char *word) {
	int i;
	char *lowerWord = (char *) malloc(sizeof(char) * 256);
	strcpy(lowerWord, word);

	// After making a copy of the original word, turn it into
	// lowercase by using the "tolower" builtin function
	for (i=0; word[i]; ++i) {
		lowerWord[i] = tolower(lowerWord[i]);
	}

	// Allocate a new list and its word, then copy the new
	// lowercase word into the StringList's word pointer
	StringList *list = (StringList *) malloc(sizeof(*list));
	list->Word = (char *) malloc(sizeof(char) * 256); strcpy(list->Word, lowerWord);
	list->Next = NULL;

	// Cleanup & Return
	free(lowerWord);
	lowerWord = 0;
	return list;
}

// Append a string list node to the end/tail of a string list
void AppendSList(StringList **head, StringList *node) {
	(*head)->Next = node;
}

// Free a string list, including all children
void FreeSList(StringList **node) {
	StringList **temp;

	while (node != NULL) {
		temp = node;
		node = &(*node)->Next;
		free(*temp); temp = 0;
	}
}

// Format output to a file according to a specification
void PrintSList(FILE *file, StringList *node) {
	StringList *temp;

	while (node != NULL) {
		temp = node;
		node = node->Next;
		fprintf(file, "\t%s\n", temp->Word);
		FreeSList(&node);
	}
}

// Return the number of strings in the string list
int SListCount(struct StringList *node) {
	int count = 0;

	while (node != NULL) {
		node = node->Next;
		count++;
	}

	return count;
}

// +-------------------+
// | Anagram Functions |
// +-------------------+

<<<<<<< HEAD
=======
// From StackOverflow user "R Sahu". You can find his post
// related to sorting character arrays at the following link:
// https://bit.ly/2UmU9oH
// (I know how to use qsort in C, but I didn't write this function
// myself. It is passed as the fourth argument to stdlib's qsort)
>>>>>>> 0fbee997... Clean up comments, refactor repo, change in/out
int ascending(void const *a, void const *b) {
	return (*(char *)a - *(char *)b);
}

// Create a new anagram node, including the string list node with the word.
struct AnagramList *MallocAList(char *word) {
	int numChars  = strlen(word);
	char *anagram = (char *) malloc(sizeof(char) * 256);

	// Sort the word and copy it for the anagram
	strcpy(anagram, word);
	qsort(anagram, numChars, sizeof(char), ascending);

	// Allocate a new list and its word list pointer for use
	// in setting up the anagram list
	StringList  *strList = (StringList *) malloc(sizeof(*strList));
	AnagramList *anaList = (AnagramList *) malloc(sizeof(*anaList));

	// Setup the anagram list itself
	anaList->Anagram = anagram;
	anaList->Words   = strList;
	anaList->Next    = NULL;

	// Cleanup & Return
	return anaList;
	free(anagram); anagram = 0;
}

void FreeAList(struct AnagramList **node) {
	AnagramList **temp;

	while (node != NULL) {
		temp = node;
		node = &(*node)->Next;
		//FreeSList(*temp->Words);
		free(*temp); temp = 0;
	}
}

void PrintAList(FILE *file, struct AnagramList *node) {
	AnagramList *temp;

	while (node != NULL) {
		temp = node;
		node = node->Next;
<<<<<<< HEAD
		fprintf(file, "%s\n", temp->Anagram);
		//PrintSList(file, temp->Words);
		//FreeAList(&node);
=======
		int numWords = SListCount(temp->Words);
		if (numWords > 0) {
			fprintf(file, "%s: %d\n", temp->Anagram, numWords);
			PrintSList(file, temp->Words);
		}
	}
}

// Add a new word to the anagram list
void AddWordAList(struct AnagramList **node, char *word) {
	AnagramList *temp = *node;
	AnagramList *old  = NULL;
	bool found = false;

	if (*node == NULL) {
		*node = MallocAList(word);
	}
	else {
		char *check = Anagramer(LowerCaser(word));
		while (temp != NULL) {
			if (strcmp(check, temp->Anagram) == 0) {
				AppendSList(&(temp->Words), MallocSList(word));
				found = true;
			}
			old = temp;
			temp = temp->Next;
		}
		if (!found) {
			old->Next = MallocAList(word);
		}
>>>>>>> 0fbee997... Clean up comments, refactor repo, change in/out
	}
}

int main(int argc, char *argv[]) {
<<<<<<< HEAD
	AnagramList *test = MallocAList("hello");
	PrintAList(stdout, test);
	free(test); test = 0;

	FILE *inFile  = stdin;
=======
	// Initialize everything we're going to need to read the lines from the
	// file
	AnagramList *node = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	// For some reason these assignments don't work like they did in the lab?
	// It gets a ton of errors if I try using stdin and stdout. This basically
	// makes it so that it requires files to work
	FILE *inFile = stdin;
>>>>>>> 0fbee997... Clean up comments, refactor repo, change in/out
	FILE *outFile = stdout;

	if (!(inFile = fopen(argv[1], "r"))) {
		fprintf(stderr, "No specified input file; exiting\n");
		exit(EXIT_FAILURE);
	}
	if (!(outFile = fopen(argv[2], "w"))) {
		fprintf(stderr, "No specified output file; exiting\n");
		exit(EXIT_FAILURE);
	}

<<<<<<< HEAD
	fprintf(outFile, "dgo : 2\n");

	// test malloc of the string lists
	char word[4]  = {'D', 'O', 'G', '\0'};
	char word2[4] = {'G', 'O', 'D', '\0'};
	StringList *list1 = MallocSList(word);
	StringList *list2 = MallocSList(word2);

	// test append
	AppendSList(&list1, list2);

	// test loop for printing and freeing the lists
	PrintSList(outFile, list1);

=======
	// Make sure to trim newlines from the input lines or else it's totally
	// messed up.
    while ((read = getline(&line, &len, inFile)) != -1) {
        int len = strlen(line);
        if (line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        AddWordAList(&node, line);
    }

	// Print all the anagrams and their original words
	PrintAList(outFile, node);
	
	// Free the Anagram Lists, their children, and the string lists
	// (This is broken right now, but it's very close to working. I
	// implemented these functions very soon after starting and just
	// never got around to making them perfect)
	// FreeAList(&node);

	// Free up the final line used for reading
	free(line);
>>>>>>> 0fbee997... Clean up comments, refactor repo, change in/out
	// close file
	if (inFile && outFile) {
		fclose(inFile);
		fclose(outFile);
	}

	return 0;
}

