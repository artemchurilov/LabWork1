#ifndef GAUSS_H
#define GAUSS_H

#include "bmp.h"
#include <cstdint>

class GaussianFilter {
public:
    GaussianFilter(int kernelSize, double sigma);
    ~GaussianFilter();

    void apply(BMPImage& image);

private:
    double* kernel;
    int kernelSize;
    double sigma;

    void generateKernel();
};

inline double clamp(double value, double min, double max) {
    return (value < min) ? min : (value > max) ? max : value;
}

#endif

