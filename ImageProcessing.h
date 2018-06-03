#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <iostream>
#include <opencv2/opencv.hpp>

#define MEDIAN_SIZE 3
#define BOTTOM_CROP 20
#define MIDDLE_CROP_CONSTANT 40

class ImageProcessing{
public:
    static cv::Mat extractLaser(const cv::Mat& laserFrame,const cv::Mat& frame);
    static cv::Mat crop(cv::Mat& input, int top);//crops the image to include on the object
    static void extractPoints(cv::Mat&, float*, float);//extract points from each line into an array   
    static int getTopCrop(cv::Mat&, cv::Mat&);
};

#endif