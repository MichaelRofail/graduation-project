#include "ImageProcessing.h"

using namespace cv;

Mat ImageProcessing::extractLaser(const Mat& laserFrame, const Mat& frame){
    Mat subframe = laserFrame - frame;//subtract the normal frame from the laser frame
    Mat red , blue, green, output;

    //extract each channel
    extractChannel(subframe, red, 2); 
    extractChannel(subframe, blue, 0);
    extractChannel(subframe, green, 1);

    unsigned char blue_thresh, green_thresh, red_thresh;
    getThreshold(blue_thresh, green_thresh, red_thresh);

    /**
     *threshold each channel where the red has the lowest threshold.
     *the subtraction can move the laser from the red channel to other channels depending
     on the original color of the object.
    **/
    threshold(blue, blue, blue_thresh, 255, THRESH_BINARY);
    threshold(green, green, green_thresh, 255, THRESH_BINARY);
    threshold(red, red, red_thresh, 255, THRESH_BINARY);

    //or all channels together after threshold
    bitwise_or(blue, green, output);
    bitwise_or(red, output, output);

    return output;
}

void ImageProcessing::getThreshold(unsigned char& blue_thresh, unsigned char& green_thresh, unsigned char& red_thresh){
    blue_thresh = 200;
    green_thresh = 200;
    red_thresh = 180;
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