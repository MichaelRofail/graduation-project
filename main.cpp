#include "ImageProcessing.h"
#include "DataProcessing.h"

#define NUM_OF_STEPS 360

using namespace std;

int main(){

	VideoCapture cam(0);

	Mat frame, image1, cropped;
	ostringstream temp;// holds the name for the frame to be saved

	
	for(int i = 0; i < NUM_OF_STEPS ;i++){
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

	float** arr = new float*[cropped.rows];//holds output points in 2d
	for(int i = 0; i<cropped.rows;i++){
		arr[i] = new float[2];
	}
	for(int i = 0; i < NUM_OF_STEPS ;i++){//post processing loop that extracts points from frames
		temp << i;
		temp << ".png";
		image1 = imread(temp.str(), 1);
		ImageProcessing::extractPoints(image1,arr);
		temp.str("");
	}		
}