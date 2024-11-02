#include <iostream>
#include "bmp.h"

int main() {
    const char* filename = "input.bmp";

    BMPImage image;
    if (image.load(filename)) {
        std::cout << "Program read file" << std::endl;

        BMPImage rotatedClockwise = image.rotate90Clockwise();
        rotatedClockwise.save("output_clockwise.bmp");
        rotatedClockwise.release();

        BMPImage rotatedCounterClockwise = image.rotate90CounterClockwise();
        rotatedCounterClockwise.save("output_counter_clockwise.bmp");
        rotatedCounterClockwise.release();

        image.release();
    } else {
        std::cerr << "Program didn't read file" << std::endl;
    }

    return 0;
}
