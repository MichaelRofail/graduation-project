#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <iostream>
#include <opencv2/opencv.hpp>

#define LASER_THRESHOLD 150 //threshold for the red laser color

using namespace cv;


class ImageProcessing{
public:
    static Mat extractLaser(const Mat& laserFrame,const Mat& frame);
    static Mat crop(Mat&);//crops the image to include on the object
    static void extractPoints(Mat&, float*);//extract points from each line into an array
private:
    static void getThreshold(uchar&, uchar&, uchar&, uchar&, uchar&, uchar&);//return the color range for the preprocess image    
};

#endif