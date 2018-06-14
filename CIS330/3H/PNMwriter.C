#include <PNMwriter.h>
#include <stdlib.h>
#include <stdio.h>
#include <image.h>

PNMwriter::PNMwriter() { }

PNMwriter::~PNMwriter() { }

void PNMwriter::Write(const char *filename) {
    // "wb" for write binary
    FILE *f_out;
    f_out = fopen(filename, "wb");

    // Grab the height and width from the input image
    int height = GetOutput()->GetHeight();
    int width  = GetOutput()->GetWidth();

    // Same as before
    int size = height * width;

    // Printing out the start of a PNM P6 file, as explained in the
    // YouTube lecture
    fprintf(f_out, "P6\n%d %d\n255\n", width, height);

    // Writing the binary data from the (edited) image now, this comes after
    // the header
    fwrite(GetOutput()->GetData(), sizeof(unsigned char) * 3, size, f_out);

    fclose(f_out);
}