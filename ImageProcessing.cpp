#include "ImageProcessing.h"

using namespace cv;

Mat ImageProcessing::extractLaser(const Mat& laserFrame, const Mat& frame){
    Mat gray, output, equalised, subframe, thresh;
    absdiff(laserFrame, frame, subframe);//subtract the normal frame from the laser frame

    cvtColor(subframe, gray, COLOR_BGR2GRAY);
    
    GaussianBlur(gray, gray, Size(5,5), 0, 0);

    threshold(gray, thresh, 0, 255, THRESH_BINARY+THRESH_OTSU);

    medianBlur(thresh, output, MEDIAN_SIZE);
    return output;
}

Mat ImageProcessing::crop(Mat& input){

    //Mat output = input(Rect((input.cols/3) + 20, input.rows/2 - 50, (input.cols/3) + 7, (input.rows/2) + 30));
    Mat output = input(Rect(630, 430, 268, 490));
    return output;
}

void ImageProcessing::extractPoints(Mat& inputMat, float* arr){
    bool found;
    int start , end;
    for( int i = 0; i < inputMat.rows; ++i){
        found = false;
        for( int j = 0; j < inputMat.cols; ++j ){
            
            //if a pixel is white set found to true and save the location to start
            if((found == false)&&(inputMat.at<uchar>(i,j) == 255)){
                start = j;
                end = start; //if no end is found 
                found = true;
            }
            //end location where the first black point is found    
            if((found == true) && (inputMat.at<uchar>(i,j) == 0)){
                end = j-1;
                break;
            }
        }
        //the point found is the average between the first and last white points found
        if(found == true)arr[i] = (start + end)/2;
        //if no point is found on a line put -1 in the array
        else arr[i] = -1;
    }
}