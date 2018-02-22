#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <iostream>
#include <opencv2/opencv.hpp>

#define LASER_THRESHOLD 150 //threshold for the red laser color

class ImageProcessing{
public:
    static cv::Mat extractLaser(const cv::Mat& laserFrame,const cv::Mat& frame);
    static cv::Mat crop(cv::Mat&);//crops the image to include on the object
    static void extractPoints(cv::Mat&, float*);//extract points from each line into an array   
private:
    //returnst the low threshold for each color to be used in extract laser function
    static void getThreshold(unsigned char& blue_thresh, unsigned char& green_thresh, unsigned char& red_thresh);
};

#endif