#include "ImageProcessing.h"
#include "DataProcessing.h"

//number of images taken as the object rotates and equal to the rotation steps my the motor
#define NUM_OF_STEPS 360

using namespace std;

int main(){

	VideoCapture cam(0);

	Mat frame, image1;//temps
	Mat cropped[NUM_OF_STEPS];//stores all the photos after processing

	for(int i = 0; i < NUM_OF_STEPS ;i++){
		cam.read(frame);

		image1 = ImageProcessing::preProcess(frame);//preprocess
		cropped[i] = ImageProcessing::crop(image1);

	   	namedWindow("orig Image", WINDOW_AUTOSIZE );
	    imshow("orig Image",frame);

	    namedWindow("cropped", WINDOW_AUTOSIZE );
		imshow("cropped",cropped[i]);
		//step
		waitKey(25);
	}

	float* arr = new float[cropped[0].rows];//holds output points from each frame in 2d
	PointCloud<PointXYZ> cloud; //stores the cloud
	cloud.width = 0;
	cloud.height = 0;

	cloud.is_dense = false;
	for(int i = 0; i < NUM_OF_STEPS; i++){//post processing loop that extracts points from frames
		ImageProcessing::extractPoints(cropped[i],arr);
		DataProcessing::generateXYZ(cloud, arr, cropped[i].rows, i, NUM_OF_STEPS);
	}	
	io::savePCDFileASCII ("my_point_cloud.pcd", cloud);
		
}