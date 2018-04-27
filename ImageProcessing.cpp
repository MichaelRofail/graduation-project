#include "ImageProcessing.h"

using namespace cv;

Mat ImageProcessing::extractLaser(const Mat& laserFrame, const Mat& frame){
    Mat gray, output, equalised, subframe;
    absdiff(laserFrame, frame, subframe);//subtract the normal frame from the laser frame

    cvtColor(subframe, gray, COLOR_BGR2GRAY);
    equalizeHist(gray , equalised);
     
    threshold(equalised, output, LASER_THRESHOLD, 255, THRESH_BINARY);

    //openening morphology to get rid of stray pixels
    int morph_size = 2;
    Mat element = getStructuringElement( 1, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
    morphologyEx(output, output, MORPH_OPEN, element);
    //medianBlur(output, output, 3);
    return output;
}

Mat ImageProcessing::crop(Mat& input){

    //Mat output = input(Rect((input.cols/3) + 20, input.rows/2 - 50, (input.cols/3) + 7, (input.rows/2) + 30));
    Mat output = input(Rect(600, 235, 268, 493));
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