#include <stdlib.h>
#include <filter.h>
#include <source.h>
#include <stdio.h>
#include <image.h>
#include <sink.h>

void Filter::Update() {
    // From Hank's live code session, modified to not use
    // C++ i/o as I don't like it very much. Also different
    // names to match mine
    char event[256];

    if (GetNumberOfInputs() >= 1 && input1 != NULL) {
        // Changed to be sprintf to put it inside of event
        sprintf(event, "%s : updating input one!", FilterName());
        Logger::LogEvent(event);
        input1->Update();
        sprintf(event, "%s : done updating input one!", FilterName());
        Logger::LogEvent(event);
    }

    if (GetNumberOfInputs() == 2 && input2 != NULL) {
        // Changed to be sprintf to put it inside of event
        sprintf(event, "%s : updating input two!", FilterName());
        Logger::LogEvent(event);
        input2->Update();
        sprintf(event, "%s : done updating input two!", FilterName());
        Logger::LogEvent(event);
    }

    sprintf(event, "%s : executing!", FilterName());
    Logger::LogEvent(event);
    Execute();
    sprintf(event, "%s : done executing!", FilterName());
    Logger::LogEvent(event);
}

void Filter::ThrowException() {
    char * event = (char *)(malloc(sizeof(char) * 256));

    sprintf(event, "No input1 for filter!");
    DataFlowException e(FilterName(), event);
    free(event);
    throw e;
}

void Filter::ThrowException2() {
    char * event = (char *)(malloc(sizeof(char) * 256));

    sprintf(event, "No input2 for filter");
    DataFlowException e(FilterName(), event);
    free(event);
    event = NULL;
    throw e;
}

void Filter::ThrowHeightException() {
    char * event = (char *)(malloc(sizeof(char) * 256));

    sprintf(event, "Heights don't match!");
    DataFlowException e(FilterName(), event);
    free(event);
    event = NULL;
    throw e;
}

void Filter::ThrowWidthException() {
    char * event = (char *)(malloc(sizeof(char) * 256));

    sprintf(event, "Widths don't match!");
    DataFlowException e(FilterName(), event);
    free(event);
    event = NULL;
    throw e;
}

void Filter::ThrowSizeException() {
    char * event = (char *)(malloc(sizeof(char) * 256));

    sprintf(event, "Sizes don't match!");
    DataFlowException e(FilterName(), event);
    free(event);
    event = NULL;
    throw e;
}

void Filter::ThrowFactorException() {
    char * event = (char *)(malloc(sizeof(char) * 256));

    sprintf(event, "Invalid factor for blender!");
    DataFlowException e(FilterName(), event);
    free(event);
    event = NULL;
    throw e;
}

void Shrinker::Execute() {
    if (Sink::GetOutput() == NULL) {
        ThrowException();
    }

    // Halve height of input image after getting it
    Image *input   = Sink::GetOutput();
    Image *output  = Shrinker::GetOutput();

    int height     = input->GetHeight();
    int width      = input->GetWidth();
    int halfHeight = height / 2;
    int halfWidth  = width / 2;

    // The temporary array that will be used for the new image
    unsigned char *temp = (unsigned char *)(malloc(halfHeight * halfWidth * 3));

    // Set the size of the output image to be the halved one
    output->SetSize(halfHeight, halfWidth);

    int inIndex  = 0;
    int outIndex = 0;
    int i, j;

    for (i=0; i<halfHeight; ++i) {
        for (j=0; j<halfWidth; ++j) {
            // Indexing (massive pain)
            inIndex  = 3 * ((width * i * 2) + (j * 2));
            outIndex = 3 * ((halfWidth * i) + j);

            temp[outIndex]     = input->GetData()[inIndex];
            temp[outIndex + 1] = input->GetData()[inIndex + 1];
            temp[outIndex + 2] = input->GetData()[inIndex + 2];
        }
    }

    output->SetData(temp);
    free(temp);
    temp = NULL;
}

void Mirror::Execute() {
    if (Sink::GetOutput() == NULL) {
        ThrowException();
    }

    Image *input  = Sink::GetOutput();
    Image *output = Source::GetOutput();

    int height = input->GetHeight();
    int width  = input->GetWidth();
    int size   = height * width * 3;

    unsigned char *temp = (unsigned char *)(malloc(size));

    output->SetSize(height, width);

    int inIndex  = 0;
    int outIndex = 0;
    int i, j, var;

    for (i=0; i<height; ++i) {
        var = 0;
        for (j=width-1; j>=0; --j) {
            inIndex  = 3 * ((i * width) + j);
            outIndex = 3 * ((i * width) + var);

            temp[outIndex]     = input->GetData()[inIndex];
            temp[outIndex + 1] = input->GetData()[inIndex + 1];
            temp[outIndex + 2] = input->GetData()[inIndex + 2];

            ++var;
        }
    }

    output->SetData(temp);
    free(temp);
    temp = NULL;
}

void Rotate::Execute() {
    if (Sink::GetOutput() == NULL) {
        ThrowException();
    }

    Image *input  = Sink::GetOutput();
    Image *output = Source::GetOutput();

    int height = input->GetHeight();
    int width  = input->GetWidth();
    int size   = height * width * 3;

    unsigned char *temp = (unsigned char *)(malloc(size));

    output->SetSize(width, height);

    int inIndex  = 0;
    int outIndex = 0;
    int i, j;

    for (i=0; i<height; ++i) {
        for (j=0; j<width; ++j) {
            inIndex  = 3 * ((width * i) + j);
            outIndex = 3 * ((height * (j + 1)) - (i + 1));

            temp[outIndex]     = input->GetData()[inIndex];
            temp[outIndex + 1] = input->GetData()[inIndex + 1];
            temp[outIndex + 2] = input->GetData()[inIndex + 2];
        }
    }

    output->SetData(temp);
    free(temp);
    temp = NULL;
}

void Grayscale::Execute() {
    if (Sink::GetOutput() == NULL) {
        ThrowException();
    }

    Image *input  = Sink::GetOutput();
    Image *output = Source::GetOutput();

    unsigned char *data = input->GetData();

    int height = input->GetHeight();
    int width  = input->GetWidth();
    int size   = height * width * 3;

    unsigned char *temp = (unsigned char *)(malloc(size));

    output->SetSize(height, width);

    int index = 0;
    int i, j;

    for (i=0; i<height; ++i) {
        for (j=0; j<width; ++j) {
            index = 3 * ((width * i) + j);

            unsigned char gray = data[index] / 5 + data[index + 1] / 2 + data[index + 2] / 4;

            temp[index]     = gray;
            temp[index + 1] = gray;
            temp[index + 2] = gray;
        }
    }

    output->SetData(temp);
    free(temp);
    temp = NULL;
}

void Blur::Execute() { 
    if (Sink::GetOutput() == NULL) {
        ThrowException();
    }

    Image *input  = Sink::GetOutput();
    Image *output = Source::GetOutput();

    unsigned char *data = input->GetData();

    int height = input->GetHeight();
    int width  = input->GetWidth();
    int size   = height * width * 3;

    unsigned char *temp = (unsigned char *)(malloc(size));

    output->SetSize(height, width);

    int index = 0;
    int i, j;
    int up, down, left, right;
    int uleft, uright, dleft, dright;
    int red, green, blue;

    for (i=0; i<height; ++i) {
        for (j=0; j<width; ++j) {
            index = 3 * ((width * i) + j);

            if ((i == 0) or i == (height - 1) or (j == 0) or (j == width - 1)) {
                temp[index]     = data[index];
                temp[index + 1] = data[index + 1];
                temp[index + 2] = data[index + 2];
            }
            else {
                left   = index - 3;
                right  = index + 3;
                up     = index - (width * 3);
                down   = index + (width * 3);
                uleft  = index - (width * 3) - 3;
                uright = index - (width * 3) + 3;
                dleft  = index + (width * 3) - 3;
                dright = index + (width * 3) + 3;

                red   = ((data[left] / 8) + (data[right] / 8) + (data[up] / 8) + (data[down] / 8) + (data[uleft] / 8) + (data[uright] / 8) + (data[dleft] / 8) + (data[dright] / 8));
                green = ((data[left + 1] / 8) + (data[right + 1] / 8) + (data[up + 1] / 8) + (data[down + 1] / 8) + (data[uleft + 1] / 8) + (data[uright + 1] / 8) + (data[dright + 1] / 8) + (data[dleft + 1] / 8));
                blue  = ((data[left + 2] / 8) + (data[right + 2] / 8) + (data[up + 2] / 8) + (data[down + 2] / 8) + (data[uleft + 2] / 8) + (data[uright + 2] / 8) + (data[dright + 2] / 8) + (data[dleft + 2] / 8));
                
                temp[index]     = red;
                temp[index + 1] = green;
                temp[index + 2] = blue;
            }
        }
    }

    output->SetData(temp);
    free(temp);
    temp = NULL;
}

void LRCombine::Execute() {
    if (Sink::GetOutput() == NULL) {
        ThrowException();
    }
    if (Sink::GetOutput2() == NULL) {
        ThrowException2();
    }

    // Get all the heights and widths from both images
    Image *leftInput  = Sink::GetOutput();
    Image *rightinput = Sink::GetOutput2();
    Image *output     = LRCombine::GetOutput();

    int heightOne = leftInput->GetHeight();
    int heightTwo = rightinput->GetHeight();
    int widthOne  = leftInput->GetWidth();
    int widthTwo  = rightinput->GetWidth();

    if (heightOne != heightTwo) {
        ThrowException();
    }

    // Getting the values of the output image (will be larger)
    int outputHeight = (heightOne + heightTwo) / 2;
    int outputWidth  = (widthOne + widthTwo);
    int size = outputHeight * outputWidth * 3;

    // Set the size using aforementioned values
    output->SetSize(outputHeight, outputWidth);

    unsigned char* temp = (unsigned char *)(malloc(size));

    int inIndex  = 0;
    int outIndex = 0;

    for (int i=0; i<widthOne; ++i) {
        for(int j=0; j<outputHeight; ++j) {
            inIndex  = 3 * ((widthOne * j) + i);
            outIndex = 3 * ((outputWidth * j) + i);

            temp[outIndex]     = leftInput->GetData()[inIndex];
            temp[outIndex + 1] = leftInput->GetData()[inIndex + 1];
            temp[outIndex + 2] = leftInput->GetData()[inIndex + 2];
        }
    }

    inIndex  = 0;
    outIndex = 0;

    for (int u=0; u<widthTwo; ++u) {
        for(int v=0; v<outputHeight; ++v) {
            inIndex  = 3 * ((widthTwo * v) + u);
            outIndex = 3 * ((outputWidth * v)+ widthOne + u);

            temp[outIndex]     = rightinput->GetData()[inIndex];
            temp[outIndex + 1] = rightinput->GetData()[inIndex + 1];
            temp[outIndex + 2] = rightinput->GetData()[inIndex + 2];
        }
    }

    output->SetData(temp);
    free(temp);
}

void TBCombine::Execute() {
    if (Sink::GetOutput() == NULL) {
        ThrowException();
    }
    if (Sink::GetOutput2() == NULL) {
        ThrowException2();
    }

    Image *topInput    = Sink::GetOutput();
    Image *bottomInput = Sink::GetOutput2();
    Image *output      = TBCombine::GetOutput();

    int heightOne = topInput->GetHeight();
    int heightTwo = bottomInput->GetHeight();
    int widthOne  = topInput->GetWidth();
    int widthTwo  = bottomInput->GetWidth();

    if (widthOne != widthTwo) {
        ThrowWidthException();
    }

    int outputHeight = (heightOne + heightTwo);
    int outputWidth  = (widthOne + widthTwo) / 2;
    int size         = outputHeight * outputWidth * 3;

    output->SetSize(outputHeight, outputWidth);

    unsigned char* temp = (unsigned char *)(malloc(size));

    int inIndex  = 0;
    int outIndex = 0;

    for (int i=0; i<outputWidth; ++i) {
        for(int j=0; j<heightOne; ++j) {
            inIndex  = 3 * (widthOne * j + i);
            outIndex = 3 * (outputWidth * j + i);

            temp[outIndex]     = topInput->GetData()[inIndex];
            temp[outIndex + 1] = topInput->GetData()[inIndex + 1];
            temp[outIndex + 2] = topInput->GetData()[inIndex + 2];
        }
    }

    inIndex  = 0;
    outIndex = 0;

    for (int u=0; u<outputWidth; ++u) {
        for(int v=0; v<heightTwo; ++v) {
            inIndex  = 3 * ((widthTwo * v)+ u);
            outIndex = 3 * ((outputWidth * (v + heightOne)) + u);

            temp[outIndex]     = bottomInput->GetData()[inIndex];
            temp[outIndex + 1] = bottomInput->GetData()[inIndex + 1];
            temp[outIndex + 2] = bottomInput->GetData()[inIndex + 2];
        }
    }

    output->SetData(temp);
    free(temp);
}

void Blender::Execute() {
    if (Sink::GetOutput() == NULL) {
        ThrowException();
    }
    if (Sink::GetOutput2() == NULL) {
        ThrowException2();
    }

    Image *input1 = Sink::GetOutput();
    Image *input2 = Sink::GetOutput2();
    Image *output = Source::GetOutput();
    double factor = GetFactor();

    if (factor > 1.0) {
        ThrowFactorException();
    }

    int heightOne = input1->GetHeight();
    int heightTwo = input2->GetHeight();
    int widthOne  = input1->GetWidth();
    int widthTwo  = input2->GetWidth();

    if (heightOne != heightTwo || widthOne != widthTwo) {
        ThrowSizeException();
    }

    int outputHeight = (heightOne + heightTwo) / 2;
    int outputWidth  = (widthOne + widthTwo) / 2;
    int size         = outputHeight * outputWidth * 3;

    output->SetSize(outputHeight, outputWidth);

    unsigned char *temp = (unsigned char *)(malloc(size));

    int index = 0;

    for (int i=0; i<outputWidth; ++i) {
        for(int j=0; j<outputHeight; ++j) {
            index  = 3 * ((outputWidth * j) + i);

            temp[index]     = input1->GetData()[index] * factor + input2->GetData()[index] * (1 - factor);
            temp[index + 1] = input1->GetData()[index + 1] * factor + input2->GetData()[index + 1] * (1 - factor);
            temp[index + 2] = input1->GetData()[index + 2] * factor + input2->GetData()[index + 2] * (1 - factor);
        }
    }

    output->SetData(temp);
    free(temp);
    temp = NULL;
}

void Subtract::Execute() {
    if (Sink::GetOutput() == NULL) {
        ThrowException();
    }
    if (Sink::GetOutput2() == NULL) {
        ThrowException2();
    }

    Image *input1 = Sink::GetOutput();
    Image *input2 = Sink::GetOutput2();
    Image *output = Source::GetOutput();

    int heightOne = input1->GetHeight();
    int heightTwo = input2->GetHeight();
    int widthOne  = input1->GetWidth();
    int widthTwo  = input2->GetWidth();

    if (heightOne != heightTwo || widthOne != widthTwo) {
        ThrowSizeException();
    }

    int size = heightOne * widthOne * 3;

    output->SetSize(heightOne, widthOne);

    unsigned char *data1 = input1->GetData();
    unsigned char *data2 = input2->GetData();
    unsigned char *temp  = (unsigned char *)(malloc(size));

    int index, index1, index2;
    int i, j;

    for (i=0; i<heightOne; ++i) {
        for(j=0; j<widthOne; ++j) {
            index  = 3 * ((widthOne * i) + j);
            index1 = index + 1;
            index2 = index + 2;

            temp[index]  = data1[index]  > data2[index]  ? (data1[index]  - data2[index]) : 0;
            temp[index1] = data1[index1] > data2[index1] ? (data1[index1] - data2[index1]) : 0;
            temp[index2] = data1[index2] > data2[index2] ? (data1[index2] - data2[index2]) : 0;
        }
    }

    output->SetData(temp);
    free(temp);
}

Color::Color(int wi, int he, unsigned char r, unsigned char g, unsigned char b) {
    width  = wi;
    height = he;
    red    = r;
    green  = g;
    blue   = b;
}

void Color::Execute() {
    Image *output = Source::GetOutput();
    output->SetSize(height, width);

    int size = height * width * 3;

    unsigned char *temp = (unsigned char *)(malloc(size));

    int i, j, index;

    for (i=0; i<height; ++i) {
        for (j=0; j<width; ++j) {
            index = 3 * ((i * width) + j);
            temp[index]     = red;
            temp[index + 1] = green;
            temp[index + 2] = blue; 
        }
    }

    output->SetData(temp);
    free(temp);
    temp = NULL;
}

void CheckSum::SetInput(Image* img) {
    input = img;
}

void CheckSum::OutputCheckSum(char* filename) {
    FILE* check_out;
    check_out = fopen(filename, "wb");

    unsigned char *data = input->GetData();

    int height = input->GetHeight();
    int width  = input->GetWidth();

    unsigned char red   = 0;
    unsigned char green = 0;
    unsigned char blue  = 0;

    int i, j, index;

    for (i=0; i<height; ++i) {
        for (j=0; j<width; ++j) {
            index  = 3 * ((width * i) + j);
            red   += data[index];
            green += data[index + 1];
            blue  += data[index + 2];
        }
    }

    fprintf(check_out, "CHECKSUM: %d, %d, %d\n", red, green, blue);
    fclose(check_out);
}