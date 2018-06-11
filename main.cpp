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
#define NUM_OF_STEPS 192
//the delay between each frame capture in ms 
#define FRAME_DELAY 20
#define LASER_DELAY 300
//camera brightness
#define BRIGHTNESS 40 
//angle between laser and normal to view plane in rad
#define LASER1_ANGLE (0.3272)
#define LASER2_ANGLE (0.3436)
//somoothing radius for resampling
#define SMOOTHING_SEARCH_RADIUS 15
//crop the bottom plate
#define BOTTOM_CROP 10
//if the camera is off center 
#define MIDDLE_CROP_CONSTANT 82
//laser offeset in degree
#define LASER2_OFFSET 80//temp

using namespace std;

int main(){

    raspicam::RaspiCam_Cv Camera;
    Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    Camera.set(CV_CAP_PROP_BRIGHTNESS, BRIGHTNESS);
    Camera.open();
    Hardware::hardwareInit();
    ostringstream ss;
    cv::Mat laserFrame, frame, flipLaserFrame, flipFrame, pimg, cropImg1, cropImg2;
    cv::Mat croppedL1[NUM_OF_STEPS];//stores all the photos after processing
    cv::Mat croppedL2[NUM_OF_STEPS];

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

    Hardware::laserOff(1);
    Hardware::laserOff(2);
    cv::waitKey(LASER_DELAY);

    for(int i = 0; i < NUM_OF_STEPS ;i++){
        //capture no laser image
        Camera.grab();
        cv::waitKey(FRAME_DELAY);
        cv::waitKey(LASER_DELAY);
        Camera.retrieve(frame);

        ss <<"imgs/";
        ss <<i;
        ss <<".jpg";
        cv::imwrite(ss.str(), frame);
        ss.str("");
        ss.clear();
        
        //capture laser 1 image
        Hardware::laserOn(1);
        Camera.grab();
        cv::waitKey(FRAME_DELAY);
        cv::waitKey(LASER_DELAY);
        Camera.retrieve(laserFrame);
        Hardware::laserOff(1);

        ss <<"imgs/";
        ss <<i;
        ss <<"l1.jpg";    
        cv::imwrite(ss.str(), laserFrame);
        ss.str("");
        ss.clear();

        //process laser 1 images
        laserFrame = ImageProcessing::crop(laserFrame, top, MIDDLE_CROP_CONSTANT, BOTTOM_CROP);
        frame = ImageProcessing::crop(frame, top, MIDDLE_CROP_CONSTANT, BOTTOM_CROP);
        pimg = ImageProcessing::extractLaser(laserFrame, frame);
        croppedL1[i] = pimg;

        //capture laser2 image
        Hardware::laserOn(2);
        Camera.grab();
        cv::waitKey(FRAME_DELAY);
        cv::waitKey(LASER_DELAY);
        Camera.retrieve(laserFrame);
        Hardware::laserOff(2);

        ss <<"imgs/";
        ss <<i;
        ss <<"l2.jpg";    
        cv::imwrite(ss.str(), laserFrame);
        ss.str("");
        ss.clear();
        
        //process laser2 images
        cv::flip(laserFrame, flipLaserFrame, 0);
        cv::flip(frame,flipFrame, 0);
        flipLaserFrame = ImageProcessing::crop(flipLaserFrame, top, MIDDLE_CROP_CONSTANT, BOTTOM_CROP);
        flipFrame = ImageProcessing::crop(flipFrame, top, MIDDLE_CROP_CONSTANT, BOTTOM_CROP);
        pimg = ImageProcessing::extractLaser(laserFrame, frame);
        croppedL2[i] = pimg;

        Hardware::motorMicroStep();
    }
    Camera.release();

    float* arr = new float[croppedL1[0].rows];//holds output points from each frame in 2d
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>); //stores the cloud
    cloud->width = 0;
    cloud->height = 0;
    cloud->is_dense = false;

    for(int i = 0; i < NUM_OF_STEPS; i++){//post processing loop that extracts points from frames
        ImageProcessing::extractPoints(croppedL1[i],arr, LASER1_ANGLE);
        DataProcessing::generateXYZ(cloud, arr, croppedL1[i].rows, i, NUM_OF_STEPS, 0);
        ImageProcessing::extractPoints(croppedL2[i],arr, LASER2_ANGLE);
        DataProcessing::generateXYZ(cloud, arr, croppedL2[i].rows, i, NUM_OF_STEPS, LASER2_OFFSET);
    }
    pcl::PointCloud<pcl::PointNormal> cloudNormals = SurfaceReconstruct::smooth(cloud, SMOOTHING_SEARCH_RADIUS);
    
    //save and load to remove normals	
    pcl::io::savePCDFileASCII ("my_point_cloud.pcd", cloudNormals);
    pcl::io::loadPCDFile<pcl::PointXYZ>("my_point_cloud.pcd", *cloud);
    
    pcl::PolygonMesh mesh = SurfaceReconstruct::reconstruct(cloud, 480);//edit num
    pcl::io::savePCDFileASCII ("my_point_cloud.pcd", *cloud);//save the cloud to a file
    pcl::io::saveOBJFile("model.obj", mesh);
}
