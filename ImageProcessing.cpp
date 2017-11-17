#include "ImageProcessing.h"

Mat ImageProcessing::preProcess(const Mat& input){

    uchar low_b,low_g,low_r,high_b,high_g,high_r;
    getThreshold(low_b, low_g, low_r, high_b, high_g, high_r);
    Mat out;
    inRange(input, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r), out);
    return out;
} 

void ImageProcessing::getThreshold(uchar& low_b, uchar& low_g, uchar& low_r, uchar& high_b, uchar& high_g, uchar& high_r){
    
    low_b = 100;
    low_g = 100;
    low_r = 200;
    high_b = 255;
    high_g = 255;
    high_r = 255;
    //get values from histogram
}

Mat ImageProcessing::crop(Mat& input){

    Mat output = input(Rect(input.cols/2,0,input.cols/2,input.rows));
    return output;
}

void ImageProcessing::extractPoints(Mat& inputMat, float* arr){
    bool found;
    for( int i = 0; i < inputMat.rows; ++i){
        found = false;
        for( int j = 0; j < inputMat.cols; ++j ){
            //if a pixel is white check next pixel if it is white too write the point in the array
            if(inputMat.at<uchar>(i,j) == 255){
                if(j < inputMat.cols - 1){
                    if(inputMat.at<uchar>(i,j+1)){
                        arr[i] = j;
                        found = true;
                    }
                }
            }    
        }
        //if no point is found on a line put -1 in the array
        if(found == false)arr[i] = -1;
    }
}