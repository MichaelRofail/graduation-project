#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <iostream>
#include <opencv2/opencv.hpp>

#define MEDIAN_SIZE 3

class ImageProcessing{
public:
    static cv::Mat extractLaser(const cv::Mat& laserFrame,const cv::Mat& frame);//turns 2 images into a binary image of the laser
    static cv::Mat crop(cv::Mat& input, int top, int middleCropConstant, int BottomCrop);//crops the image around the object
    static void extractPoints(cv::Mat&, float* arr, float laserAngle);//extract points from each line into an array   
    static int getTopCrop(cv::Mat& img1, cv::Mat& img2);
};

#endif