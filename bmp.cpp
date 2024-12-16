/* Artem Churilov st130184@student.spbu.ru
   LabWork1 task "Rotation and Filtering of BMP Image"
*/

#include "bmp.h"
#include <iostream>
#include <cstring>

BMPImage::BMPImage() : pixelData(nullptr) {}

BMPImage::~BMPImage()
{
    release();
}
const BMPFileHeader& BMPImage::getFileHeader() const
{
    return fileHeader;
}

const BMPInfoHeader& BMPImage::getInfoHeader() const
{
    return infoHeader;
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
        std::cerr << "Error in file type" << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    uint32_t dataSize = calculateMemorySize();
    pixelData = new uint8_t[dataSize];
    if (!pixelData)
    {
        std::cerr << "Error: Not enough memory." << std::endl;
        return false;
    }

    file.seekg(fileHeader.dataOffset, std::ios::beg);
    file.read(reinterpret_cast<char*>(pixelData), dataSize);

    return true;
}

bool BMPImage::save(const char* filename)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error in file creating " << filename << std::endl;
        return false;
    }

    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    uint32_t dataSize = calculateMemorySize();
    file.seekp(fileHeader.dataOffset, std::ios::beg);
    file.write(reinterpret_cast<const char*>(pixelData), dataSize);

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

BMPImage BMPImage::rotate90Clockwise() const
{
    BMPImage rotatedImage;

    rotatedImage.infoHeader = infoHeader;
    rotatedImage.infoHeader.width = infoHeader.height;
    rotatedImage.infoHeader.height = infoHeader.width;

    uint32_t rowSize = ((infoHeader.bitsPerPixel * infoHeader.width + 3) / 32) * 4;
    uint32_t newRowSize = ((infoHeader.bitsPerPixel * rotatedImage.infoHeader.width + 31) / 32) * 4;
    uint32_t dataSize = newRowSize * rotatedImage.infoHeader.height;

    rotatedImage.pixelData = new uint8_t[dataSize];
    rotatedImage.fileHeader = fileHeader;
    rotatedImage.fileHeader.fileSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + dataSize;

    for (int y = 0; y < infoHeader.height; ++y)
    {
        for (int x = 0; x < infoHeader.width; ++x)
        {
            int srcIndex = y * rowSize + x * (infoHeader.bitsPerPixel / 8);
            int dstIndex = x * newRowSize + (rotatedImage.infoHeader.width-y-1) * (infoHeader.bitsPerPixel / 8);

            std::memcpy(&rotatedImage.pixelData[dstIndex], &pixelData[srcIndex], infoHeader.bitsPerPixel / 8);
        }
    }

    return rotatedImage;
}

BMPImage BMPImage::rotate90CounterClockwise() const
{
    BMPImage rotatedImage;

    rotatedImage.infoHeader = infoHeader;
    rotatedImage.infoHeader.width = infoHeader.height;
    rotatedImage.infoHeader.height = infoHeader.width;

    uint32_t rowSize = ((infoHeader.bitsPerPixel * infoHeader.width + 3) / 32) * 4;
    uint32_t newRowSize = ((infoHeader.bitsPerPixel * rotatedImage.infoHeader.width + 31) / 32) * 4;
    uint32_t dataSize = newRowSize * rotatedImage.infoHeader.height;

    rotatedImage.pixelData = new uint8_t[dataSize];
    rotatedImage.fileHeader = fileHeader;
    rotatedImage.fileHeader.fileSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + dataSize;

    for (int y = 0; y < infoHeader.height; ++y)
    {
        for (int x = 0; x < infoHeader.width; ++x)
        {
            int srcIndex = y * rowSize + x * (infoHeader.bitsPerPixel / 8);
            int dstIndex = (rotatedImage.infoHeader.height - x - 1) * newRowSize + y * (infoHeader.bitsPerPixel / 8);

            std::memcpy(&rotatedImage.pixelData[dstIndex], &pixelData[srcIndex], infoHeader.bitsPerPixel / 8);
        }
    }

    return rotatedImage;
}

