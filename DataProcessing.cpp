#include "DataProcessing.h"

void DataProcessing::generateXYZ(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, float* arr, int arrSize, int currentStep, int numOfSteps, float offset){
    int numOfPoints = 0;//holds the actual number of points to be added to the cloud
    for(int i = 0; i < arrSize; i++){
        if(arr[i] > 0)numOfPoints++;
    }
    cloud->width += numOfPoints;
    cloud->height = 1;
    cloud->points.resize (cloud->width * cloud->height);//resize the cloud to make space for more points

    double angle = double((360 * currentStep) / numOfSteps) + (double)offset;
    angle = (angle / 180) * 3.14159; //convert degree to rad
    float cosAngle = cos(angle), sinAngle = sin(angle);
    
    for(int j = 0, i = (cloud->width - numOfPoints); i < cloud->width && j < arrSize; j++){
        if(arr[j] > 0){//if a point in the array not -1 add it to the cloud
            cloud->points[i].x = arr[j]*cosAngle;
            cloud->points[i].y = arrSize - j;
            cloud->points[i].z = arr[j]*sinAngle;
            i++;
        }
    }
}