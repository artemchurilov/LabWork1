/* Artem Churilov st130184@student.spbu.ru
   LabWork4 task "Paralleling of Rotation and Filtering of BMP Image"
*/

/** 
 * @file bmp.h
 * @brief BMP image processing header
 * 
 * Defines structures and class for BMP image loading, saving, and manipulation.
 */

#ifndef BMP_H
#define BMP_H

#include <cstdint>
#include <fstream>

#pragma pack(push, 1)

/**
 * @struct BMPFileHeader
 * @brief BMP file header structure (14 bytes)
 */
struct BMPFileHeader
{
    uint16_t fileType;      ///< File type ("BM")
    uint32_t fileSize;      ///< File size in bytes
    uint16_t reserved1;     ///< Reserved field (unused)
    uint16_t reserved2;     ///< Reserved field (unused)
    uint32_t dataOffset;    ///< Pixel data offset from file start
};

/**
 * @struct BMPInfoHeader
 * @brief BMP information header (40 bytes)
 */
struct BMPInfoHeader
{
    uint32_t headerSize;        ///< Header size (40 bytes)
    int32_t width;              ///< Image width in pixels
    int32_t height;             ///< Image height in pixels
    uint16_t planes;            ///< Color planes (must be 1)
    uint16_t bitsPerPixel;      ///< Bits per pixel (24, 32, etc.)
    uint32_t compression;       ///< Compression method (0 = none)
    uint32_t imageSize;         ///< Image data size (bytes)
    int32_t xPixelsPerMeter;    ///< Horizontal resolution (pixels/meter)
    int32_t yPixelsPerMeter;    ///< Vertical resolution (pixels/meter)
    uint32_t colorsUsed;        ///< Number of color indices used
    uint32_t importantColors;   ///< Number of important colors
};

#pragma pack(pop)

/**
 * @class BMPImage
 * @brief BMP image loading, processing and saving class
 */
class BMPImage
{
public:
    BMPImage();
    ~BMPImage();

    /**
     * @brief Load BMP image from file
     * @param filename Path to BMP file
     * @return True if loaded successfully
     */
    bool load(const char* filename);

    /**
     * @brief Save image to BMP file
     * @param filename Output file path
     * @return True if saved successfully
     */
    bool save(const char* filename);

    /// @brief Release allocated pixel data
    void release();

    /**
     * @brief Calculate image memory size
     * @return Memory size in bytes
     */
    uint32_t calculateMemorySize() const;

    /// @brief Get BMP file header
    const BMPFileHeader& getFileHeader() const;

    /// @brief Get BMP info header
    const BMPInfoHeader& getInfoHeader() const;

    /**
     * @brief Rotate image 90° clockwise (original)
     * @return Rotated BMP image
     */
    BMPImage rotate90Clockwise() const;

    /**
     * @brief Rotate image 90° counter-clockwise (original)
     * @return Rotated BMP image
     */
    BMPImage rotate90CounterClockwise() const;

    /**
     * @brief Rotate image 90° clockwise (optimized)
     * @return Rotated BMP image
     */
    BMPImage newRotate90Clockwise() const;

    /**
     * @brief Rotate image 90° counter-clockwise (optimized)
     * @return Rotated BMP image
     */
    BMPImage newRotate90CounterClockwise() const;

    uint8_t* pixelData;  ///< Raw pixel data array

private:
    BMPFileHeader fileHeader;  ///< BMP file header
    BMPInfoHeader infoHeader;  ///< BMP info header
};

#endif