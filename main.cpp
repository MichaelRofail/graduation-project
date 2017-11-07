#include "ImageProcessing.h"

using namespace std;

int main(){

	VideoCapture cam(0);

	Mat frame ,image1,image2;

	while(1){
		cam.read(frame);

		image1 = ImageProcessing::preProcess(frame);//preprocess
		image2 = ImageProcessing::crop(image1);

	   	namedWindow("orig Image", WINDOW_AUTOSIZE );
	    imshow("orig Image",frame);

	    namedWindow("Image1", WINDOW_AUTOSIZE );
	    imshow("Image1",image2);
	    waitKey(25);
	}
}