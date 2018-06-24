#include "SurfaceReconstruct.h"

pcl::PolygonMesh SurfaceReconstruct::reconstruct(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, float centroidY){
    // Normal estimation
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud (cloud);
    n.setInputCloud(cloud);
    n.setSearchMethod(tree);
    n.setKSearch(0);
    n.setRadiusSearch(20);
    n.setViewPoint(0, centroidY, 0);//edit
    n.compute(*normals);

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
    //poisson.setScale(1.0001);
    //point weight 
    pcl::PolygonMesh mesh;
    poisson.reconstruct(mesh);
    return mesh;
}

pcl::PointCloud<pcl::PointNormal> SurfaceReconstruct::smooth(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, int searchRadius){

    // Create a KD-Tree
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
    // Output has the PointNormal type in order to store the normals calculated by MLS
    pcl::PointCloud<pcl::PointNormal> mls_points;
    // Init object (second point type is for the normals, even if unused)
    pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointNormal> mls;
    mls.setComputeNormals(true);

    // Set parameters
    mls.setInputCloud(cloud);
    mls.setPolynomialFit(true);
    mls.setSearchMethod(tree);
    mls.setSearchRadius(searchRadius);

    // Reconstruct
    mls.process(mls_points);
    return mls_points;
}