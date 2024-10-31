#include "bmp.h"
#include <iostream>
#include <cstring>

BMPImage::BMPImage() : pixelData(nullptr) {}

BMPImage::~BMPImage()
{
    release();
}

bool BMPImage::load(const char* filename)
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
        std::cerr <<  "Error in file type"  << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    uint32_t dataSize = calculateMemorySize();
    pixelData = new uint8_t[dataSize];
    if (!pixelData)
    {
        std::cerr << "Error: not enough memory." << std::endl;
        return false;
    }

    file.seekg(fileHeader.dataOffset, std::ios::beg);
    file.read(reinterpret_cast<char*>(pixelData), dataSize);

    return true;
}

void BMPImage::release()
{
    delete[] pixelData;
    pixelData = nullptr;
}

uint32_t BMPImage::calculateMemorySize() const
{
    uint32_t rowSize = ((infoHeader.bitsPerPixel * infoHeader.width + 31) / 32) * 4;
    return rowSize * abs(infoHeader.height);
}
