#include <logging.h>
#include <source.h>
#include <stdlib.h>
#include <string.h>
#include <image.h>

Source::Source() {
    output->SetSource(this);
}

Source::~Source() {
    delete output;
    output = NULL;
}

Image * Source::GetOutput() { 
    return output;
}

void Source::Update() {
    char *event = (char *)(malloc(sizeof(char) * 256));

    sprintf(event, "%s : executing!", SourceName());
    Logger::LogEvent(event);
    Execute();
    sprintf(event, "%s : done executing!", SourceName());
    Logger::LogEvent(event);

    free(event);
    event = NULL;
}