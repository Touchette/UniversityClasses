#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <image.h>
#include <source.h>
#include <logging.h>

Image::Image() {
    height = 0;
    width  = 0;
    array  = NULL;
}

Image::Image(int he, int wi, unsigned char *arr) {
    int size = 3 * he * wi;
    height   = he;
    width    = wi;
    array    = (unsigned char *)(malloc(size));

    memcpy(array, arr, size);
}

Image::Image(Image &image) {
    int size = 3 * height * width;
    height   = image.height;
    width    = image.width;
    array    = (unsigned char *)(malloc(size));

    memcpy(array, image.array, size);
}

Image::~Image() {
    free(array);
}

void Image::SetSize(int he, int wi) {
    height = he;
    width  = wi;
}

void Image::SetData(unsigned char *arr) {
    if (array == NULL) {
        array = (unsigned char*)(malloc(3 * height * width));
    }

    memcpy(array, arr, 3 * height * width);
}

void Image::SetSource(Source *s) {
    source = s;
}

void Image::Update() const {
    if (source == NULL) {
        fprintf(stderr, "Cannot update image no source\n");
        exit(EXIT_FAILURE);
    }
    source->Update();
}