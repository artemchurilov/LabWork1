/* Artem Churilov st130184@student.spbu.ru
   LabWork1 task "Rotation and Filtering of BMP Image"
*/

#include <iostream>
#include "bmp.h"
#include "gauss.h"

int main() {
    const char* filename = "input.bmp";
    BMPImage image;
    if (image.load(filename)) {
        std::cout << "Program read file" << std::endl;
        GaussianFilter filter(5, 1.0);
        filter.apply(image);
        BMPImage rotatedClockwise = image.rotate90Clockwise();
        if (rotatedClockwise.save("output_rotated_clockwise.bmp"))
        {
            std::cout << "Saved rotated clockwise image as output_rotated_clockwise.bmp." << std::endl;
        }
        else
        {
            std::cerr << "Failed to save the rotated clockwise image." << std::endl;
        }
        rotatedClockwise.release();

        BMPImage rotatedCounterClockwise = image.rotate90CounterClockwise();
        if (rotatedCounterClockwise.save("output_rotated_counterclockwise.bmp"))
        {
            std::cout << "Saved rotated counterclockwise image as output_rotated_counterclockwise.bmp." << std::endl;
        }
        else
        {
            std::cerr << "Failed to save the rotated counterclockwise image." << std::endl;
        }
        rotatedCounterClockwise.release();

        image.release();
    } else {
        std::cerr << "Program didn't read file" << std::endl;
    }

    return 0;
}

