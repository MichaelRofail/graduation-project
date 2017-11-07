#include "ImageProcessing.h"
#include "DataProcessing.h"

using namespace std;

int main(){

	VideoCapture cam(0);

	Mat frame, image1, cropped;
	ostringstream temp;// holds the name for the frame to be saved

	for(int i = 0; i < 360 ;i++){
		cam.read(frame);

		image1 = ImageProcessing::preProcess(frame);//preprocess
		cropped = ImageProcessing::crop(image1);

		temp << i;
		temp << ".png";
		imwrite(temp.str(), cropped);//write image to file

	   	namedWindow("orig Image", WINDOW_AUTOSIZE );
	    imshow("orig Image",frame);

	    namedWindow("cropped", WINDOW_AUTOSIZE );
		imshow("cropped",cropped);

		temp.str("");//clear stream
		//step
		waitKey(25);
	}
}