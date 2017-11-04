#include "ImageProcessing.h"

int main(){

	VideoCapture cam(0);

	Mat frame;// = imread("frame.png",1);//read image
	Mat image1;// = imread("frame.png",0);//force image2 into type uchar
	cam.read(image1);
	cvtColor(image1, image1, COLOR_RGB2GRAY);

	while(1){
		cam.read(frame);
		ImageProcessing::preProcess(frame,image1);//preprocess

	   	namedWindow("orig Image", WINDOW_AUTOSIZE );
	    imshow("orig Image",frame);

	    namedWindow("Image1", WINDOW_AUTOSIZE );
	    imshow("Image1",image1);
	    waitKey(25);
	}
}