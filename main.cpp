/**This is the main file for the 3D scanner
 * 
 * Run this program with any argument for test mode where the program reads
 *  images from the same folder instead of the camera 
**/
#include <raspicam/raspicam_cv.h>
#include "ImageProcessing.h"
#include "DataProcessing.h"
#include "SurfaceReconstruct.h"
#include "Hardware.h"

//number of images taken as the object rotates and equal to the rotation steps of the motor
#define NUM_OF_STEPS 50
//the delay between each frame capture in ms 
#define FRAME_DELAY 600
//camera brightness
#define BRIGHTNESS 20 

using namespace std;

int main(){

	Hardware::motorInit();
	cv::Mat laserFrame, frame, image1;//temps
	cv::Mat cropped[NUM_OF_STEPS];//stores all the photos after processing
	
	raspicam::RaspiCam_Cv Camera;
	Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
	Camera.set(CV_CAP_PROP_BRIGHTNESS, BRIGHTNESS);
    Camera.set(CV_CAP_PROP_WHITE_BALANCE_BLUE_U, 50);
	Camera.open();

	for(int i = 0; i < NUM_OF_STEPS ;i++){
		
		Camera.grab();
		Hardware::laserOn();
		cv::waitKey(FRAME_DELAY);
		Camera.retrieve(laserFrame);

		Camera.grab();
		Hardware::laserOff();
		cv::waitKey(FRAME_DELAY);
		Camera.retrieve(frame);

		image1 = ImageProcessing::extractLaser(laserFrame, frame);
		cropped[i] = ImageProcessing::crop(image1);

		cv::namedWindow("orig Image", cv::WINDOW_AUTOSIZE );
		cv::imshow("orig Image",frame);

		cv::namedWindow("cropped", cv::WINDOW_AUTOSIZE );
		cv::imshow("cropped",cropped[i]);
		
		Hardware::motorStep();
	}
	Camera.release();

	float* arr = new float[cropped[0].rows];//holds output points from each frame in 2d
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>); //stores the cloud
	cloud->width = 0;
	cloud->height = 0;
	cloud->is_dense = false;

	for(int i = 0; i < NUM_OF_STEPS; i++){//post processing loop that extracts points from frames
		ImageProcessing::extractPoints(cropped[i],arr);
		DataProcessing::generateXYZ(cloud, arr, cropped[i].rows, i, NUM_OF_STEPS);
	}	
	pcl::io::savePCDFileASCII ("my_point_cloud.pcd", *cloud);//save the cloud to a file

	pcl::PolygonMesh mesh = SurfaceReconstruct::reconstruct(cloud);
	pcl::io::saveOBJFile("model.obj", mesh);
}
