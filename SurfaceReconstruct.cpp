#include "SurfaceReconstruct.h"

pcl::PolygonMesh SurfaceReconstruct::reconstruct(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){
    // Normal estimation
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud (cloud);
    n.setInputCloud (cloud);
    n.setSearchMethod (tree);
    n.setKSearch (20);
    n.compute (*normals);

    for(int i = 0; i < normals->size(); ++i){
        normals->points[i].normal_x *= -1;
        normals->points[i].normal_y *= -1;
        normals->points[i].normal_z *= -1;
    }
    
    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals (new pcl::PointCloud<pcl::PointNormal>);
    concatenateFields (*cloud, *normals, *cloud_with_normals);
    pcl::Poisson<pcl::PointNormal> poisson;
    poisson.setDepth(POISSON_DEPTH);
    poisson.setInputCloud(cloud_with_normals);
    pcl::PolygonMesh mesh;
    poisson.reconstruct(mesh);
    return mesh;
}