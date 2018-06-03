#include "ImageProcessing.h"

using namespace cv;

Mat ImageProcessing::extractLaser(const Mat& laserFrame, const Mat& frame){
    Mat gray, output, equalised, subframe, thresh;
    absdiff(laserFrame, frame, subframe);//subtract the normal frame from the laser frame

    cvtColor(subframe, gray, COLOR_BGR2GRAY);
    
    GaussianBlur(gray, gray, Size(5,5), 0, 0);

    threshold(gray, thresh, 0, 255, THRESH_BINARY+THRESH_OTSU);

    //int morph_size = 1;
    //Mat element = getStructuringElement( 1, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
    //morphologyEx( thresh, output, 0, element);
    medianBlur(thresh, output, MEDIAN_SIZE);
    return output;
}

Mat ImageProcessing::crop(Mat& input, int top){

    Mat output = input(Rect((input.cols/2) + MIDDLE_CROP_CONSTANT, top, (input.cols/2) - MIDDLE_CROP_CONSTANT, input.rows - top - BOTTOM_CROP));
    //Mat output = input(Rect(676, 427, 127, 518));
    return output;
}

int ImageProcessing::getTopCrop(cv::Mat& img1, cv::Mat& img2){
    int top;
    cv::Mat img;
    cv::absdiff(img1, img2, img);
    cvtColor(img, img, COLOR_BGR2GRAY);
    GaussianBlur(img, img, Size(5,5), 0, 0);
    threshold(img, img, 0, 255, THRESH_BINARY+THRESH_OTSU);
    medianBlur(img, img, 5);
    for( int i = 0; i < img.rows; i++){
        for( int j = 0; j < img.cols; j++){
            if(img.at<uchar>(i,j) == 255)return i;
        }
    }
    return top;
}

void ImageProcessing::extractPoints(Mat& inputMat, float* arr, float laserAngle){
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
        if(found == true){
            arr[i] = (start + end)/2;
            arr[i] /= sin(laserAngle);
        }
        //if no point is found on a line put -1 in the array
        else arr[i] = -1;
    }
}