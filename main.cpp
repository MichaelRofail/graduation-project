//This is the main file for the 3D scanner

#include "ImageProcessing.h"
#include "DataProcessing.h"
#include "SurfaceReconstruct.h"

//number of images taken as the object rotates and equal to the rotation steps of the motor
#define NUM_OF_STEPS 192
//the delay between each frame capture in ms 
#define FRAME_DELAY 5
#define LASER1_ANGLE (0.52)
#define LASER2_ANGLE (0.52)//temp
#define SMOOTHING_SEARCH_RADIUS 15
#define BOTTOM_CROP 20
#define MIDDLE_CROP_CONSTANT 40
#define LASER2_OFFSET 80//temp

using namespace std;

int main(void){

    cv::VideoCapture cam(0);
    cv::Mat laserFrame, frame, flipLaserFrame, flipFrame, pimg, cropImg1, cropImg2;
    cv::Mat croppedL1[NUM_OF_STEPS];//stores all the photos after processing
    cv::Mat croppedL2[NUM_OF_STEPS];
    ostringstream ss;

    //calculate crop
    cropImg1 = cv::imread("imgs/crop1.jpg");
    cropImg2 = cv::imread("imgs/crop2.jpg");
    int top = ImageProcessing::getTopCrop(cropImg1, cropImg2);

    for(int i = 0; i < NUM_OF_STEPS ;i++){
        ss <<"imgs/";
        ss <<i;
        ss <<"l1.jpg";    
        laserFrame = cv::imread(ss.str());   
        
        ss.str("");
        ss.clear();
        ss <<"imgs/";
        ss <<i;
        ss <<".jpg";
        frame = cv::imread(ss.str());
        ss.str("");
        ss.clear();

        cv::namedWindow("orig Image", cv::WINDOW_NORMAL);
        cv::imshow("orig Image",frame);

        cv::namedWindow("laser Image", cv::WINDOW_NORMAL);
        cv::imshow("laser Image",laserFrame);

        laserFrame = ImageProcessing::crop(laserFrame, top, MIDDLE_CROP_CONSTANT, BOTTOM_CROP);
        frame = ImageProcessing::crop(frame, top, MIDDLE_CROP_CONSTANT, BOTTOM_CROP);
        pimg = ImageProcessing::extractLaser(laserFrame, frame);
        croppedL1[i] = pimg;

        ss <<"imgs/";
        ss <<i;
        ss <<"l2.jpg";    
        laserFrame = cv::imread(ss.str());
        ss.str("");
        ss.clear();

        cv::flip(laserFrame, flipLaserFrame, 0);
        cv::flip(frame,flipFrame, 0);
        flipLaserFrame = ImageProcessing::crop(flipLaserFrame, top, MIDDLE_CROP_CONSTANT, BOTTOM_CROP);
        flipFrame = ImageProcessing::crop(flipFrame, top, MIDDLE_CROP_CONSTANT, BOTTOM_CROP);
        pimg = ImageProcessing::extractLaser(laserFrame, frame);
        croppedL2[i] = pimg;

        cv::namedWindow("cropped", cv::WINDOW_AUTOSIZE);
        cv::imshow("cropped",croppedL1[i]);
        cv::waitKey(FRAME_DELAY);
    }

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

    //save and load to remoe normals	
    pcl::io::savePCDFileASCII ("my_point_cloud.pcd", cloudNormals);
    pcl::io::loadPCDFile<pcl::PointXYZ>("my_point_cloud.pcd", *cloud);
    
    pcl::PolygonMesh mesh = SurfaceReconstruct::reconstruct(cloud, 480);//edit num
    pcl::io::savePCDFileASCII ("my_point_cloud.pcd", *cloud);//save the cloud to a file
    pcl::io::saveOBJFile("model.obj", mesh);
}