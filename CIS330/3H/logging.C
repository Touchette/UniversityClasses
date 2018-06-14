#include <logging.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Logger file
FILE *Logger::logger = NULL;

DataFlowException::DataFlowException(const char *type, const char *error) {
    sprintf(msg, "%s: Exception thrown! %s", type, error);
    Logger::LogEvent(msg);
}

void Logger::LogEvent(const char *event) {
	if (logger == NULL) {
		logger = fopen("log", "w");
	}
    fwrite(event, sizeof(char), strlen(event), logger);
    fwrite("\n", sizeof(char), strlen("\n"), logger);
}

void Logger::Finalize() {
    fclose(logger);
}