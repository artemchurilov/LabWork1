/* Artem Churilov st130184@student.spbu.ru
   LabWork1 task "Rotation and Filtering of BMP Image"
*/

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
// Чтобы функция встраивалась, ее определение должно быть вместе с объявлением в заголовке (
inline double clamp(double value, double min, double max);
#endif

