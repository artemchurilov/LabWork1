/* Artem Churilov st130184@student.spbu.ru
   LabWork1 task "Rotation and Filtering of BMP Image"
*/

#ifndef BMP_H
#define BMP_H

#include <cstdint>
#include <fstream>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
};

struct BMPInfoHeader {
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

class BMPImage {
// Зачем делать это классом, если всё в нем публичное? Спрячь данные и методы, которые не должны быть доступны пользователю в private
public:
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    uint8_t* pixelData;

    BMPImage();
    ~BMPImage();

    bool load(const char* filename);
    bool save(const char* filename);
    void release();
    uint32_t calculateMemorySize() const;

    BMPImage rotate90Clockwise() const;
    BMPImage rotate90CounterClockwise() const;
};

#endif
