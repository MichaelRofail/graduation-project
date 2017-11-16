#include "ImageProcessing.h"
#include "DataProcessing.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

 //number of images taken as the object rotates and equal to the rotation steps my the motor
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

	float* arr = new float[cropped.rows];//holds output points from each frame in 2d
	pcl::PointCloud<pcl::PointXYZ> cloud; //stores the cloud

 	// Fill in the cloud data
 	cloud.width    = NUM_OF_STEPS;
	cloud.height   = cropped.rows;
	cloud.is_dense = false;
	cloud.points.resize (cloud.width * cloud.height);

	for(int i = 0; i < NUM_OF_STEPS; i++){//post processing loop that extracts points from frames
		temp << i;
		temp << ".png";
		image1 = imread(temp.str(), 1);
		ImageProcessing::extractPoints(image1,arr);
		temp.str("");
	}		
}