#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <iostream>
#include <cmath>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

using namespace std;

class DataProcessing{
    public:
    //transforms xy points in an array to xyz and fill point cloud
    static void generateXYZ(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud , float* arr, int arrSize, int currentStep, int numOfSteps, float offset);
};

#endif