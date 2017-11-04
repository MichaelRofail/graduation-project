#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class ImageProcessing{
public:
    static void preProcess(const Mat& input, const Mat& output){

        uchar low_b,low_g,low_r,high_b,high_g,high_r;
        getThreshold(low_b, low_g, low_r, high_b, high_g, high_r);

        inRange(input, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r), output);
    } 
    static void getThreshold(uchar& low_b, uchar& low_g, uchar& low_r, uchar& high_b, uchar& high_g, uchar& high_r){
        low_b = 100;
        low_g = 100;
        low_r = 200;
        high_b = 255;
        high_g = 255;
        high_r = 255;
        //get values from histogram
    }

};

#endif