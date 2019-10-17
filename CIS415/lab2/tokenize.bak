/*
 * Description: tokenizes user input so that each "command" is read
 * and separated by a semicolon delimiter
 *
 * Author: Natalie Letz #951463883
 *
 * Date: 2019-10-07
 *
 * Notes:
 *     1. I didn't understand quite how to use getline() and still
 *     have the ">>> " appear before user input as if I were using
 *     scanf(), so it just outputs it in the while loop (quite ugly)
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);

	/* Main function variables & allocation of memory for input */
	// Delimiter & token pointer to be used by strotok()
	const char *delimiter = " \t\n\f\r\v";
	char *token;

	// The in / out streams used for writing, by default going
	// to be stdin and stdout
	FILE *instream;
	FILE *outstream;

	// The variables used for getline() calls
	char *line = 0;
	size_t len = 0;
	ssize_t nread;

	// Setting up the streams
	instream  = stdin;
	outstream = stdout;
	if (argc > 1) {
		instream = fopen(argv[1], "r");
		outstream = fopen("pseudoshell_output.txt", "w");
		if (instream == NULL || outstream == NULL) {
			perror("fopen");
			exit(1);
		}
	}

	/* Main run loop */
	int i = 0;
	while (((outstream == stdout) ? printf(">>> ") : 1) 
		&& (nread = getline(&line, &len, instream)) != -1) {
		// Tokenize the input string
		token = strtok(line, delimiter);

		// Exit successfully if we get an exit command, do nothing if we
		// get empty input
		if (token != NULL) {
			if (strcmp(token, "exit") == 0) {
				printf("\n");
				break;
			}
		} else {
			continue;
		}

		// Given output has a newline before displaying the tokens
		printf("\n");
		while (token != NULL) {
			if (outstream != NULL) {
				fprintf(outstream, "T%d: %s\n", i, token);
			} else {
				printf("T%d: %s\n", i, token);
			}

			token = strtok(NULL, delimiter);
			i++;
		}

		// Reset token counter
		i = 0;
	}
	
	/* Memory cleanup & closing files */
	free(line);
	if (instream != stdin) {
		fclose(instream);
		fclose(outstream);
	}

	return 0;
}