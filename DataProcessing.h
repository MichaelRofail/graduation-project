#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

using namespace pcl;

class DataProcessing{
    //transforms xy points in an array to xyz an fill point cloud
    static void generateXYZ(PointCloud<PointXYZ>& , float*, int);
};

#endif