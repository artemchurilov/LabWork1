/* Artem Churilov st130184@student.spbu.ru
   LabWork4 task "Paralleling of Rotation and Filtering of BMP Image"
*/

/** 
 * @file gauss.h
 * @brief Gaussian filter implementation
 * 
 * Defines Gaussian filter class for image smoothing operations.
 */

#ifndef GAUSS_H
#define GAUSS_H

#include "bmp.h"
#include <cstdint>

/**
 * @class GaussianFilter
 * @brief Gaussian blur filter implementation
 */
class GaussianFilter
{
public:
    /**
     * @brief Construct Gaussian filter
     * @param kernelSize Kernel dimension (odd number)
     * @param sigma Gaussian standard deviation
     */
    GaussianFilter(int kernelSize, double sigma);
    
    ~GaussianFilter();

    /**
     * @brief Apply filter to image (original)
     * @param image Target BMP image
     */
    void apply(BMPImage& image);

    /**
     * @brief Apply filter to image (optimized)
     * @param image Target BMP image
     */
    void newApply(BMPImage& image);

private:
    double* kernel;     ///< Convolution kernel array
    int kernelSize;     ///< Kernel dimension
    double sigma;       ///< Gaussian standard deviation

    /// @brief Generate convolution kernel
    void generateKernel();
};

/**
 * @brief Clamp value between min and max
 * @param value Input value
 * @param min Minimum bound
 * @param max Maximum bound
 * @return Clamped value
 */
inline double clamp(double value, double min, double max)
{
    return (value < min) ? min : (value > max) ? max : value;
};

#endif