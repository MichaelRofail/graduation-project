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
#include "BLUETOOTH.h"

//number of images taken as the object rotates and equal to the rotation steps of the motor
#define NUM_OF_STEPS 192
//the delay between each frame capture in ms 
#define FRAME_DELAY 200
//camera brightness
#define BRIGHTNESS 40 
//camera between laser and normal to view plane
#define LASER1_ANGLE (0.52)
//somoothing radius for resampling
#define SMOOTHING_SEARCH_RADIUS 15
//crop the bottom plate
#define BOTTOM_CROP 20
//if the camera is off center 
#define MIDDLE_CROP_CONSTANT 40

using namespace std;

int main(int argc, char **argv){

	int client;
	int s,i;
	client = Xconnect(&s);
	char buf[1024] = { 0 };
	int bytes_read;
	While(buf != "TF"){
    
    bytes_read = read(client, buf, sizeof(buf));
    if( bytes_read > 0 ) {
        printf("received [%s]\n", buf);
    }
	
    raspicam::RaspiCam_Cv Camera;
    Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    Camera.set(CV_CAP_PROP_BRIGHTNESS, BRIGHTNESS);
    Camera.open();
    Hardware::hardwareInit();
    ostringstream ss;
    cv::Mat laserFrame, frame, image1, cropImg1, cropImg2;//temps
    cv::Mat cropped[NUM_OF_STEPS];//stores all the photos after processing
    
    //to give time for the camera to reach stablility
    Camera.grab();
    cv::waitKey(FRAME_DELAY);
    Camera.retrieve(laserFrame);
    cv::imwrite("imgs/crop1.jpg", laserFrame);

    Camera.grab();
    cv::waitKey(FRAME_DELAY);
       Camera.retrieve(cropImg1);
    for(int i = 0; i < 20 ;i++){
        Hardware::motorMicroStep();
    }
    Camera.grab();
    cv::waitKey(FRAME_DELAY);
       Camera.retrieve(cropImg2);
    int top = ImageProcessing::getTopCrop(cropImg1, cropImg2);
    cv::imwrite("imgs/crop1.jpg", cropImg1);
    cv::imwrite("imgs/crop2.jpg", cropImg2);

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

        laserFrame = ImageProcessing::crop(laserFrame, top, MIDDLE_CROP_CONSTANT, BOTTOM_CROP);
        frame = ImageProcessing::crop(frame, top, MIDDLE_CROP_CONSTANT, BOTTOM_CROP);
        image1 = ImageProcessing::extractLaser(laserFrame, frame);
        cropped[i] = image1;
        
        Hardware::motorMicroStep();
    }
    Hardware::laserOff(1);
    Camera.release();

    float* arr = new float[cropped[0].rows];//holds output points from each frame in 2d
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>); //stores the cloud
    cloud->width = 0;
    cloud->height = 0;
    cloud->is_dense = false;

    for(int i = 0; i < NUM_OF_STEPS; i++){//post processing loop that extracts points from frames
        ImageProcessing::extractPoints(cropped[i], arr, LASER1_ANGLE);
        DataProcessing::generateXYZ(cloud, arr, cropped[i].rows, i, NUM_OF_STEPS);
    }
    pcl::PointCloud<pcl::PointNormal> cloudNormals = SurfaceReconstruct::smooth(cloud, SMOOTHING_SEARCH_RADIUS);
    
    //save and load to remove normals	
    pcl::io::savePCDFileASCII ("my_point_cloud.pcd", cloudNormals);
    pcl::io::loadPCDFile<pcl::PointXYZ>("my_point_cloud.pcd", *cloud);
    
    pcl::PolygonMesh mesh = SurfaceReconstruct::reconstruct(cloud, 480);//edit num
    pcl::io::savePCDFileASCII ("my_point_cloud.pcd", *cloud);//save the cloud to a file
    pcl::io::saveOBJFile("model.obj", mesh);
}
}
