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
// myself; it is passed as the fourth argument to stdlib's qsort.)
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

	return lowerWord;
}

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
		printf("%d\n", numWords);
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

	FILE *inFile = stdin;
	FILE *outFile = stdout;

	if (!(inFile = fopen(argv[1], "r"))) {
		fprintf(stderr, "No specified input file; using stdin\n");
	}
	if (!(outFile = fopen(argv[2], "w"))) {
		fprintf(stderr, "No specified output file; using stdout\n");
	}

    while ((read = getline(&line, &len, inFile)) != -1) {
        int len = strlen(line);
        if (line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        AddWordAList(&node, line);
    }

	// AddWordAList(&node, "doG");
	// AddWordAList(&node, "God");
	// AddWordAList(&node, "odG");
	// AddWordAList(&node, "gDo");
	// AddWordAList(&node, "nIgger");
	// AddWordAList(&node, "gingEr");


	// Print all the anagrams and their original words
	PrintAList(outFile, node);
	
	// Free the Anagram Lists, their children, and the string lists
	// FreeAList(&node);

	free(line);
	// close file
	if (inFile && outFile) {
		fclose(inFile);
		fclose(outFile);
	}

	return 0;
}
