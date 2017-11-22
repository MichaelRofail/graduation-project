#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <iostream>
#include <cmath>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

using namespace pcl;
using namespace std;

class DataProcessing{
    public:
    //transforms xy points in an array to xyz and fill point cloud
    static void generateXYZ(PointCloud<PointXYZ>& , float*, int, int, int);
};

#endif