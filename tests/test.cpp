/* Artem Churilov st130184@student.spbu.ru
   LabWork4 task "Paralleling of Rotation and Filtering of BMP Image"
*/

#include <gtest/gtest.h>
#include <iostream>
#include "../include/bmp.h"
#include "../include/gauss.h"
#include <chrono>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(MainTest, SpeedTest)
{
    const char* filename = "input.bmp";
    BMPImage image;
    image.load(filename);
    

        std::cout << "Program read file" << std::endl;
        GaussianFilter filter(5, 1.0);
        filter.apply(image);


        auto start = std::chrono::high_resolution_clock::now();
        BMPImage rotatedCounterClockwise = image.rotate90CounterClockwise();
        BMPImage rotatedClockwise = image.rotate90Clockwise();
        auto end = std::chrono::high_resolution_clock::now();

        auto newstart = std::chrono::high_resolution_clock::now();
        BMPImage newrotatedClockwise = image.newRotate90Clockwise();
        BMPImage newrotatedCounterClockwise = image.newRotate90CounterClockwise();
        auto newend = std::chrono::high_resolution_clock::now();

        rotatedClockwise.release();
        newrotatedClockwise.release();

        rotatedCounterClockwise.release();
        newrotatedCounterClockwise.release();

        image.release();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        auto newduration = std::chrono::duration_cast<std::chrono::milliseconds>(newend - newstart);
        std::cout<<(duration.count()-newduration.count())<<"\n";
        std::cout<<(float(duration.count())/float(newduration.count()))<<"\n";
    EXPECT_TRUE(duration.count()-newduration.count()>0);
}

TEST(MainTest, GaussTest)
{
    const char* filename = "input.bmp";
    BMPImage image;
    image.load(filename);
    

        std::cout << "Program read file" << std::endl;
        GaussianFilter filter(5, 1.0);
        auto start = std::chrono::high_resolution_clock::now();
        filter.apply(image);
        auto end = std::chrono::high_resolution_clock::now();

        auto newstart = std::chrono::high_resolution_clock::now();
        filter.newApply(image);
        auto newend = std::chrono::high_resolution_clock::now();





        image.release();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        auto newduration = std::chrono::duration_cast<std::chrono::milliseconds>(newend - newstart);
        std::cout<<(duration.count()-newduration.count())<<"\n";
        std::cout<<(float(duration.count())/float(newduration.count()))<<"\n";
    EXPECT_TRUE(duration.count()-newduration.count()>0);
}

TEST(MainTest, FinalTest)
{
    const char* filename = "input.bmp";
    BMPImage image;
    image.load(filename);
    

        std::cout << "Program read file" << std::endl;
        GaussianFilter filter(5, 1.0);

        auto newstart = std::chrono::high_resolution_clock::now();
        filter.newApply(image);
        BMPImage newrotatedClockwise = image.newRotate90Clockwise();
        BMPImage newrotatedCounterClockwise = image.newRotate90CounterClockwise();
        auto newend = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::high_resolution_clock::now();
        filter.apply(image);
        BMPImage rotatedCounterClockwise = image.rotate90CounterClockwise();
        BMPImage rotatedClockwise = image.rotate90Clockwise();
        auto end = std::chrono::high_resolution_clock::now();

        rotatedClockwise.release();
        newrotatedClockwise.release();

        rotatedCounterClockwise.release();
        newrotatedCounterClockwise.release();

        image.release();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        auto newduration = std::chrono::duration_cast<std::chrono::milliseconds>(newend - newstart);
        std::cout<<(duration.count()-newduration.count())<<"\n";
        std::cout<<(float(duration.count())/float(newduration.count()))<<"\n";
    EXPECT_TRUE(duration.count()-newduration.count()>0);
}
