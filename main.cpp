#include "ImageProcessing.h"
#include "DataProcessing.h"

using namespace std;

int main(){

	VideoCapture cam(0);

	Mat frame, image1, cropped;

	while(1){
		cam.read(frame);

		image1 = ImageProcessing::preProcess(frame);//preprocess
		cropped = ImageProcessing::crop(image1);

	   	namedWindow("orig Image", WINDOW_AUTOSIZE );
	    imshow("orig Image",frame);

	    namedWindow("cropped", WINDOW_AUTOSIZE );
	    imshow("cropped",cropped);
	    waitKey(25);
	}
}