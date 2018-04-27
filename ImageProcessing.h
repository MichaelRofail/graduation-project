#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <iostream>
#include <opencv2/opencv.hpp>

#define LASER_THRESHOLD 253

class ImageProcessing{
public:
    static cv::Mat extractLaser(const cv::Mat& laserFrame,const cv::Mat& frame);
    static cv::Mat crop(cv::Mat&);//crops the image to include on the object
    static void extractPoints(cv::Mat&, float*);//extract points from each line into an array   
};

#endif