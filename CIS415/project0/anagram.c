// +------------------------------------------+
// | Name: Natalie Letz                       |
// | Duck ID: nletz (#951463883)              |
// | CIS 415 Project 0                        |
// | This is my own work except that ...      |
// |	The "ascending" function came from    |
// |	StackOverflow. Find more info about   |
// |	that attached to the function itself. |
// +------------------------------------------+

#include "anagram.h"

// Just in case
typedef enum { false, true } bool;

typedef struct StringList StringList;
typedef struct AnagramList AnagramList;

// +----------------------+
// | StringList Functions |
// +----------------------+

// Create a new string list node
StringList *MallocSList(char *word) {
	// Allocate a new list and its word, then copy the
	// lowercase word into the StringList's word pointer
	StringList *list = (StringList *) malloc(sizeof(*list));
	list->Word = (char *) malloc(sizeof(char) * (strlen(word) + 1)); 
	strcpy(list->Word, word);
	list->Next = NULL;

	// Cleanup & Return
	return list;
}

// Append a string list node to the end/tail of a string list
void AppendSList(StringList **head, StringList *node) {
	while ((*head)->Next != NULL) {
		head = &(*head)->Next;
	}

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

// +-----------------------+
// | AnagramList Functions |
// +-----------------------+

// From StackOverflow user "R Sahu". You can find his post
// related to sorting character arrays at the following link:
// https://bit.ly/2UmU9oH
// (I know how to use qsort in C, but I didn't write this function
<<<<<<< HEAD
// myself; it is passed as the fourth argument to stdlib's qsort.)
=======
// myself. It is passed as the fourth argument to stdlib's qsort)
>>>>>>> d408d4c809f0ec59e49102f9e7a774bba06c3cac
int ascending(void const *a, void const *b) {
	return (*(char *)a - *(char *)b);
}

// Turns a word lowercase
char *LowerCaser(char *word) {
	int i;
	char *lowerWord = (char *) malloc(sizeof(char) * (strlen(word) + 1));
	strcpy(lowerWord, word);

	// After making a copy of the original word, turn it into
	// lowercase by using the "tolower" builtin function
	for (i=0; word[i]; ++i) {
		lowerWord[i] = tolower(lowerWord[i]);
	}
<<<<<<< HEAD

	return lowerWord;
}

=======

	return lowerWord;
}

>>>>>>> d408d4c809f0ec59e49102f9e7a774bba06c3cac
// Turns a word into an anagram
char *Anagramer(char *word) {
	// Set up the new string and copy the old one into it
	int numChars  = strlen(word);
	char *anagram = (char *) malloc(sizeof(char) * (strlen(word) + 1));
	strcpy(anagram, word);

	// Sort the anagram
	qsort(anagram, numChars, sizeof(char), ascending);

	return anagram;
}

// Create a new anagram node, including the string list node with the word.
struct AnagramList *MallocAList(char *word) {
	// Allocate a new list and its word list pointer for use
	// in setting up the anagram list
	AnagramList *anaList = (AnagramList *) malloc(sizeof(*anaList));
	// char *anagram = Anagramer(word);

	// Setup the anagram list itself
	anaList->Words   = MallocSList(word);
	anaList->Anagram = Anagramer(LowerCaser(word));
	anaList->Next    = NULL;

	// Cleanup & Return
	return anaList;
}

// Free an anagram list, including anagram children and string list words
void FreeAList(struct AnagramList **node) {
	AnagramList **temp;

	while (*node != NULL) {
		temp = node;
		node = &(*node)->Next;
		FreeSList(&(*temp)->Words);
		free(*temp); temp = 0;
	}
}

// Format output to a file, print anagram list with words, according to spec
void PrintAList(FILE *file, struct AnagramList *node) {
	AnagramList *temp;

	while (node != NULL) {
		temp = node;
		node = node->Next;
		int numWords = SListCount(temp->Words);
<<<<<<< HEAD
		printf("%d\n", numWords);
=======
>>>>>>> d408d4c809f0ec59e49102f9e7a774bba06c3cac
		if (numWords > 0) {
			fprintf(file, "%s: %d\n", temp->Anagram, numWords);
			PrintSList(file, temp->Words);
		}
<<<<<<< HEAD
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
		printf("word: %s, len: %ld, check: %s, len: %ld\n", word, strlen(word), check, strlen(check));
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
	}
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr, "Not enough arguments; exiting\n");
		exit(EXIT_FAILURE);
	}

	AnagramList *node = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

=======
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
	}
}

int main(int argc, char *argv[]) {
	// Initialize everything we're going to need to read the lines from the
	// file
	AnagramList *node = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	// For some reason these assignments don't work like they did in the lab?
	// It gets a ton of errors if I try using stdin and stdout. This basically
	// makes it so that it requires files to work
>>>>>>> d408d4c809f0ec59e49102f9e7a774bba06c3cac
	FILE *inFile = stdin;
	FILE *outFile = stdout;

	if (!(inFile = fopen(argv[1], "r"))) {
		fprintf(stderr, "No specified input file; using stdin\n");
	}
	if (!(outFile = fopen(argv[2], "w"))) {
		fprintf(stderr, "No specified output file; using stdout\n");
	}

<<<<<<< HEAD
=======
	// Make sure to trim newlines from the input lines or else it's totally
	// messed up.
>>>>>>> d408d4c809f0ec59e49102f9e7a774bba06c3cac
    while ((read = getline(&line, &len, inFile)) != -1) {
        int len = strlen(line);
        if (line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        AddWordAList(&node, line);
    }

<<<<<<< HEAD
	// AddWordAList(&node, "doG");
	// AddWordAList(&node, "God");
	// AddWordAList(&node, "odG");
	// AddWordAList(&node, "gDo");
	// AddWordAList(&node, "nIgger");
	// AddWordAList(&node, "gingEr");


=======
>>>>>>> d408d4c809f0ec59e49102f9e7a774bba06c3cac
	// Print all the anagrams and their original words
	PrintAList(outFile, node);
	
	// Free the Anagram Lists, their children, and the string lists
<<<<<<< HEAD
	// FreeAList(&node);

=======
	// (This is broken right now, but it's very close to working. I
	// implemented these functions very soon after starting and just
	// never got around to making them perfect)
	// FreeAList(&node);

	// Free up the final line used for reading
>>>>>>> d408d4c809f0ec59e49102f9e7a774bba06c3cac
	free(line);
	// close file
	if (inFile && outFile) {
		fclose(inFile);
		fclose(outFile);
	}

	return 0;
}
