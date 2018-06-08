#include <stdio.h>
#include <stdlib.h>
#include <filter.h>
#include <sink.h>
#include <source.h>
#include <image.h>

void Filter::Update() {
    // From Hank's live code session, modified to not use
    // C++ i/o as I don't like it very much. Also different
    // names to match mine
    char msg[256];

    if (GetNumberOfInputs() >= 1 && input1 != NULL) {
        // Changed to be sprintf to put it inside of msg
        sprintf(msg, "%s : updating input one!", FilterName());
        Logger::LogEvent(msg);
        input1->Update();
        sprintf(msg, "%s : done updating input one!", FilterName());
        Logger::LogEvent(msg);
    }

    if (GetNumberOfInputs() == 2 && input2 != NULL) {
        // Changed to be sprintf to put it inside of msg
        sprintf(msg, "%s : updating input two!", FilterName());
        Logger::LogEvent(msg);
        input2->Update();
        sprintf(msg, "%s : done updating input two!", FilterName());
        Logger::LogEvent(msg);
    }

    sprintf(msg, "%s : executing!", FilterName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s : done executing!", FilterName());
    Logger::LogEvent(msg);
}

void Filter::ThrowException() {
    char msg[256];

    sprintf(msg, "No input1 for filter!");
    DataFlowException e(FilterName(), msg);
    throw e;
}

void Filter::ThrowException2() {
    char msg[256];

    sprintf(msg, "No input2 for filter");
    DataFlowException e(FilterName(), msg);
    throw e;
}

void Filter::ThrowHeightException() {
    char msg[256];

    sprintf(msg, "Heights don't match!");
    DataFlowException e(FilterName(), msg);
    throw e;    
}

void Filter::ThrowWidthException() {
    char msg[256];

    sprintf(msg, "Widths don't match!");
    DataFlowException e(FilterName(), msg);
    throw e;
}

void Filter::ThrowSizeException() {
    char msg[256];

    sprintf(msg, "Sizes don't match!");
    DataFlowException e(FilterName(), msg);
    throw e;
}

void Filter::ThrowFactorException() {
    char msg[256];

    sprintf(msg, "Invalid factor for blender!");
    DataFlowException e(FilterName(), msg);
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

    int inIndex = 0;
    int outIndex = 0;

    for (int i=0; i<halfHeight; ++i) {
        for (int j=0; j<halfWidth; ++j) {
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

    unsigned char* temp = (unsigned char *)(malloc(size));

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
}

void CheckSum::SetInput(Image* img) {
    input = img;
}

void CheckSum::OutputCheckSum(char* filename) {
    FILE* check_out;
    check_out = fopen(filename, "wb");

    unsigned char* data = input->GetData();

    int height = input->GetHeight();
    int width  = input->GetWidth();

    int red   = 0;
    int green = 0;
    int blue  = 0;

    int i, j, index;

    for (i=0; i<height; ++i) {
        for (j=0; j<width; ++j) {
            index  = (i * width + j) * 3;
            red   += data[index];
            green += data[index + 1];
            blue  += data[index + 2];
        }
    }

    red   %= 256;
    green %= 256;
    blue  %= 256;

    fprintf(check_out, "CHECKSUM: %d, %d, %d\n", red, green, blue);
}