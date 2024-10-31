#include <iostream>
#include "bmp.h"

int main()
{
    const char* filename = "input.bmp";

    BMPImage image;
    if (image.load(filename))
    {
        std::cout << "Great! Program readed file" << std::endl;
        std::cout << "Memory for pixels " << image.calculateMemorySize() << " byte" << std::endl;

        image.release();
    }
    else
    {
        std::cerr << "Error in reading file." << std::endl;
    }

    return 0;
}
