#ifndef BMP_H
#define BMP_H

#include <cstdint>
#include <fstream>

#pragma pack(push, 1)
struct BMPFileHeader
{
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
};

struct BMPInfoHeader
{
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t importantColors;
};
#pragma pack(pop)

class BMPImage
{
public:
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    uint8_t* pixelData;

    BMPImage();
    ~BMPImage();

    bool load(const char* filename);
    void release();
    uint32_t calculateMemorySize() const;
};

#endif
