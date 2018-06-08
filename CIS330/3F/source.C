#include <source.h>
#include <image.h>
#include <logging.h>
#include <stdlib.h>
#include <string.h>

Source::Source() {
    output->SetSource(this);
}

Image * Source::GetOutput() { 
    return output;
}

void Source::Update() {
    char *msg = (char *)(malloc(sizeof(char) * 256)); 

    sprintf(msg, "%s : executing!", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf("%s : done executing!", SourceName());
    Logger::LogEvent(msg);

    free(msg);
}