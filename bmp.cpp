#include "bmp.h"
#include <iostream>

bool readBMPHeaders(const char* filename, BMPFileHeader& fileHeader, BMPInfoHeader& infoHeader) 
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) 
    {
        std::cerr << "Error in opening file " << filename << std::endl;
        return false;
    }
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    if (fileHeader.fileType != 0x4D42) 
    { 
        std::cerr << "Error in file type" << std::endl;
        return false;
    }
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    return true;
}
