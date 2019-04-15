#include "anagram.h"

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
	list->Word = (char *) malloc(sizeof(char) * 256);
	strcpy(list->Word, lowerWord);

	// Cleanup & Return
	free(lowerWord);
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
		free(*temp);
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

int main(int argc, char *argv[]) {
	FILE *inFile;
	FILE *outFile;
	bool thing = true;

	if (!(inFile = fopen(argv[1], "r"))) {
		fprintf(stderr, "No specified input file; exiting\n");
		exit(EXIT_FAILURE);
	}
	if (!(outFile = fopen(argv[2], "w"))) {
		fprintf(stderr, "No specified output file; exiting\n");
		exit(EXIT_FAILURE);
	}

	if (thing) {
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

		// close file
		if (inFile && outFile) {
			fclose(inFile);
			fclose(outFile);
		}
	}

	return 0;
}
