#include "DataProcessing.h"

void DataProcessing::generateXYZ(PointCloud<PointXYZ>& cloud, float* arr, int arrSize, int currentStep, int numOfSteps){
    int numOfPoints = 0;
    for(int i = 0; i < arrSize; i++){
        if(arr[i] > 0)numOfPoints++;
    }
    cloud.width += numOfPoints;
    cloud.height = 1;
    cloud.points.resize (cloud.width * cloud.height);
    for(int j = 0, i = (cloud.width - numOfPoints); i < cloud.width && j < arrSize;){
        if(arr[j] > 0){
            cloud.points[i].x = arr[j]*cos(numOfSteps/(360*currentStep));
            cloud.points[i].y = arrSize - j;
            cloud.points[i].z = sqrt(cloud.points[i].x*cloud.points[i].x + arr[j]*arr[j]);
            j++;
            i++;
        }else{
            j++;
        }
    }
}