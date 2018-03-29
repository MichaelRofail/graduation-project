#include "ImageProcessing.h"

using namespace cv;

Mat ImageProcessing::extractLaser(const Mat& laserFrame, const Mat& frame){
    Mat subframe = laserFrame - frame;//subtract the normal frame from the laser frame
    Mat gray, output, equalised;

    cvtColor(subframe, gray, COLOR_BGR2GRAY);

    static Ptr<CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(20);
    clahe->apply(gray, equalised);
     
    threshold(equalised, output, LASER_THRESHOLD, 255, THRESH_BINARY);
    return output;
}

Mat ImageProcessing::crop(Mat& input){

    Mat output = input(Rect((input.cols/3) + 20, input.rows/2, (input.cols/3) + 7, (input.rows/2)- 30));
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