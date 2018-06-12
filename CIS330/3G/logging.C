#include <logging.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Logger file
FILE *Logger::logger = fopen("log", "w");

DataFlowException::DataFlowException(const char *type, const char *error) {
    sprintf(msg, "%s: Exception thrown! %s", type, error);
    Logger::LogEvent(msg);
}

void Logger::LogEvent(const char *event) {
    fwrite(event, sizeof(char), strlen(event), logger);
    fwrite("\n", sizeof(char), strlen("\n"), logger);
}

void Logger::Finalize() {
    fclose(logger);
}