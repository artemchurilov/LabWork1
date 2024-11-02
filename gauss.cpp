/* Artem Churilov st130184@student.spbu.ru
   LabWork1 task "Rotation and Filtering of BMP Image"
*/

#include "gauss.h"
#include <iostream>
#include <cmath>
#include <cstring>

GaussianFilter::GaussianFilter(int kernelSize, double sigma)
: kernelSize(kernelSize), sigma(sigma) {
    kernel = new double[kernelSize * kernelSize];
    generateKernel();
}

GaussianFilter::~GaussianFilter() {
    delete[] kernel;
}

void GaussianFilter::generateKernel()
{
    double sum = 0.0;
    int halfSize = kernelSize / 2;

    for (int y = -halfSize; y <= halfSize; ++y) {
        for (int x = -halfSize; x <= halfSize; ++x) {
            double value = (1.0 / (2.0 * M_PI * sigma * sigma)) *
                          exp(-(x * x + y * y) / (2.0 * sigma * sigma));
            kernel[(y + halfSize) * kernelSize + (x + halfSize)] = value;
            sum += value;
        }
    }

    for (int i = 0; i < kernelSize * kernelSize; ++i)
    {
        kernel[i] /= sum;
    }
}

void GaussianFilter::apply(BMPImage& image)
{
    int width = image.infoHeader.width;
    int height = image.infoHeader.height;
    int channels = image.infoHeader.bitsPerPixel / 8;

    uint8_t* newPixelData = new uint8_t[width * height * channels];

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            double colorSum[3] = {0.0};
            double weightSum = 0.0;

            for (int ky = -kernelSize / 2; ky <= kernelSize / 2; ++ky)
            {
                for (int kx = -kernelSize / 2; kx <= kernelSize / 2; ++kx)
                {
                    int srcX = clamp(x + kx, 0, width - 1);
                    int srcY = clamp(y + ky, 0, height - 1);

                    int srcIndex = (srcY * width + srcX) * channels;
                    double weight = kernel[(ky + kernelSize / 2) * kernelSize + (kx + kernelSize / 2)];

                    for (int c = 0; c < channels; ++c) {
                        colorSum[c] += image.pixelData[srcIndex + c] * weight;
                    }
                    weightSum += weight;
                }
            }

            int dstIndex = (y * width + x) * channels;
            for (int c = 0; c < channels; ++c)
            {
                newPixelData[dstIndex + c] = static_cast<uint8_t>(clamp(colorSum[c], 0.0, 255.0));
            }
        }
    }

    delete[] image.pixelData;
    image.pixelData = newPixelData;
}
