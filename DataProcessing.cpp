#include "DataProcessing.h"

void DataProcessing::generateXYZ(PointCloud<PointXYZ>& cloud, float* arr, int arrSize, int currentStep, int numOfSteps){
    int numOfPoints = 0;//holds the actual number of points to be added to the cloud
    for(int i = 0; i < arrSize; i++){
        if(arr[i] > 0)numOfPoints++;
    }
    cloud.width += numOfPoints;
    cloud.height = 1;
    cloud.points.resize (cloud.width * cloud.height);//resize the cloud to make space for more points

    for(int j = 0, i = (cloud.width - numOfPoints); i < cloud.width && j < arrSize;){
        if(arr[j] > 0){//if a point in the array not -1 add it to the cloud
            cloud.points[i].x = arr[j]*cos(numOfSteps/(360*currentStep));
            cloud.points[i].y = arrSize - j;
            cloud.points[i].z = sqrt(cloud.points[i].x * cloud.points[i].x + arr[j] * arr[j]);
            j++;
            i++;
        }else{
            j++;
        }
    }
}