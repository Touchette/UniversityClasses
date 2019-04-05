#ifndef ANAGRAM_H
#define ANAGRAM_H

#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// +---------+
// | Structs |
// +---------+
// List of strings structure
struct StringList {
	struct	StringList* Next;
	char *Word;
};

// List of anagrams structure
struct AnagramList {
	struct StringList *Words;
	struct AnagramList *Next;
	char *Anagram;
};

// +-----------+
// | Functions |
// +-----------+
// Create a new string list node
struct StringList *MallocSList(char *word);

// Append a string list node to the end/tail of a string list
void AppendSList(struct StringList **head, struct StringList *node);

// Free a string list, including all children
void FreeSList(struct StringList **node);

// Format output to a file according to a specification
void PrintSList(FILE *file,struct StringList *node);

// Return the number of strings in the string list
int SListCount(struct StringList *node);

//Create a new anagram node, including the string list node with the word
struct AnagramList* MallocAList(char *word);

// Free an anagram list, including anagram children and string list words
void FreeAList(struct AnagramList **node);

// Format output to a file, print anagram list with words, according to spec
void PrintAList(FILE *file,struct AnagramList *node);

// Add a new word to the anagram list
void AddWordAList(struct AnagramList **node, char *word);

#endif
