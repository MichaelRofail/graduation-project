#ifndef SurfaceReconstruct_H
#define SurfaceReconstruct_H

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/obj_io.h>
#include <pcl/surface/poisson.h>

#define POISSON_DEPTH 5

class SurfaceReconstruct{
    public:
    static pcl::PolygonMesh reconstruct(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
};

#endif