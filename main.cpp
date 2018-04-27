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
#define NUM_OF_STEPS 96
//the delay between each frame capture in ms 
#define FRAME_DELAY 200
//camera brightness
#define BRIGHTNESS 40 

using namespace std;

int main(){

    Hardware::hardwareInit();
    cv::Mat laserFrame, frame, image1;//temps
    cv::Mat cropped[NUM_OF_STEPS];//stores all the photos after processing
    
    raspicam::RaspiCam_Cv Camera;
    Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    Camera.set(CV_CAP_PROP_BRIGHTNESS, BRIGHTNESS);
    Camera.open();
	//to give time for the camera to reach stablility
	Camera.grab();
	cv::waitKey(FRAME_DELAY);
    Camera.retrieve(laserFrame);
	
    ostringstream ss;

    for(int i = 0; i < NUM_OF_STEPS ;i++){
        
        Camera.grab();
        Hardware::laserOn(1);
        cv::waitKey(FRAME_DELAY);
        Camera.retrieve(laserFrame);

        ss <<"imgs/";
        ss <<i;
        ss <<"l.jpg";    
        cv::imwrite(ss.str(), laserFrame);
        ss.str("");
        ss.clear();
        
        ss <<"imgs/";
        ss <<i;
        ss <<".jpg";
    
        Camera.grab();
        Hardware::laserOff(1);
        cv::waitKey(FRAME_DELAY);
        Camera.retrieve(frame);

        cv::imwrite(ss.str(), frame);
        ss.str("");
        ss.clear();

        image1 = ImageProcessing::extractLaser(laserFrame, frame);
        cropped[i] = ImageProcessing::crop(image1);
        
        Hardware::motorStep();
    }
    Hardware::laserOff(1);
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
