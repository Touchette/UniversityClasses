#include <PNMreader.h>
#include <stdio.h>
#include <stdlib.h>
#include <image.h>
#include <string.h>

PNMreader::PNMreader(char *fn) {
    filename = (char *)(malloc(strlen(fn) + 1));
    strcpy(filename, fn);
}


PNMreader::~PNMreader() {
    if (filename != NULL) {
        free(filename);
    }
}

void PNMreader::Update() {
    Execute();
}

void PNMreader::Execute() {
    // "rb" for read binary
    FILE *f_in;
    f_in = fopen(filename, "rb");
    
    // Check if we actually read a file
    if (f_in == NULL) {
        fprintf(stderr, "Unable to open file \"%s\".\n", filename);
        exit(1);
    }

    // These 3 lines given by Hank
    char magicNum[128];
    int width, height, maxval;
    // From the YouTube lecture, this is the start of a PNM P6 file
    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

    // This gets used a lot, give it a variable to make code more readable
    int size = height * width;

    // An array for me to store the data in temporarily before assigning
    // it to an Image object
    unsigned char *temp = (unsigned char *)(malloc(sizeof(unsigned char) * size * 3));

    // Read in the binary data from the file which is in the form of
    // unsigned chars, this is a 3 dimensional array that Hank spoke
    // about in the YouTube lecture which was easier to read in my opinion
    // (I tried using a pixel struct and couldn't find out how to read well)
    fread(temp, sizeof(unsigned char) * 3, size, f_in);

    // Set the image we were passed
    GetOutput()->SetSize(height, width);
    GetOutput()->SetData(temp);

    // Close file, can free temp here because we don't need it anymore
    fclose(f_in);
    free(temp);
}