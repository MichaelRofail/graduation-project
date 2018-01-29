#include "ImageProcessing.h"

Mat ImageProcessing::extractLaser(const Mat& laserFrame, const Mat& frame){
    Mat subframe = laserFrame - frame;
    extractChannel(subframe, subframe, 2); //extract red channel only 
    threshold(subframe, subframe, LASER_THRESHOLD, 255,THRESH_BINARY);
    return subframe;
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