#include <iostream>
#include "bmp.h"

int main() 
{
    const char* filename = "input.bmp";

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    if (readBMPHeaders(filename, fileHeader, infoHeader)) 
    {
        std::cout << "Great! Program readed file" << std::endl;
        std::cout << "File Size: " << fileHeader.fileSize << " byte" << std::endl;
        std::cout << "Offset: " << fileHeader.dataOffset << " byte" << std::endl;
        
        std::cout << "Header Size: " << infoHeader.headerSize << std::endl;
        std::cout << "Width: " << infoHeader.width << std::endl;
        std::cout << "Height: " << infoHeader.height << std::endl;
        std::cout << "Bits Per Pixel: " << infoHeader.bitsPerPixel << std::endl;
        std::cout << "ColorsUsed: " << infoHeader.colorsUsed << std::endl;
    }
    else 
    {
        std::cerr << "Error in reading file." << std::endl;
    }

    return 0;
}
