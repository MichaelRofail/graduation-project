/**This is the main file for the 3D scanner
 * 
 * Run this program with any argument for test mode where the program reads
 *  images from the same folder instead of the camera 
**/
#include "ImageProcessing.h"
#include "DataProcessing.h"
#include "SurfaceReconstruct.h"

//number of images taken as the object rotates and equal to the rotation steps of the motor
#define NUM_OF_STEPS 96
//the delay between each frame capture in ms 
#define FRAME_DELAY 100

using namespace std;

int main(int argc, char** argv){

	cv::VideoCapture cam(0);
	cv::Mat laserFrame, frame, image1;//temps
	cv::Mat cropped[NUM_OF_STEPS];//stores all the photos after processing
	ostringstream ss;

	for(int i = 0; i < NUM_OF_STEPS ;i++){
		ss <<"imgs/";
		ss <<i;
        ss <<"l.jpg";    
        laserFrame = cv::imread(ss.str());   
		
		ss.str("");
        ss.clear();
		ss <<"imgs/";
        ss <<i;
        ss <<".jpg";
	    frame = cv::imread(ss.str());
		ss.str("");
        ss.clear();

		image1 = ImageProcessing::extractLaser(laserFrame, frame);
		cropped[i] = ImageProcessing::crop(image1);

		cv::namedWindow("orig Image", cv::WINDOW_NORMAL);
		cv::imshow("orig Image",frame);

        cv::namedWindow("laser Image", cv::WINDOW_NORMAL);
		cv::imshow("laser Image",laserFrame);

		cv::namedWindow("cropped", cv::WINDOW_NORMAL);
		cv::imshow("cropped",cropped[i]);
		cv::waitKey(FRAME_DELAY);
	}

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