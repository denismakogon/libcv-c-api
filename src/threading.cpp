//
//  threading.cpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 03.07.2022.
//

#include <stdio.h>
#include <thread>
#include <string>
#include <vector>
#include <queue>

#include "opencv2/core/mat.hpp"
#include "opencv2/dnn.hpp"

#include "include/debug.hpp"
#include "include/dnn.hpp"
#include "include/export.hpp"
#include "include/to_string.hpp"


using namespace std;
using namespace cv;
using namespace cv::dnn;

thread create_tasks(Net& net, Mat& frame, int index,
                    vector<string>& cocoClasses,
                    queue<PositionalFrameObjectDetectionDescriptor>& results,
                    double confidenceThresholdMin=0.1,
                    double confidenceThresholdMax=1.0,
                    int inputSize=640) {
    thread t([&net, &frame, &index, &cocoClasses,
               &confidenceThresholdMin,
               &confidenceThresholdMax, &results, &inputSize] () {
        PositionalFrameObjectDetectionDescriptor pds;
        vector<ObjectDetectionDescriptor> ds;

        _runObjectDetectionsOn(frame, net, ds, cocoClasses,
                               confidenceThresholdMin,
                               confidenceThresholdMax,
                               inputSize);
        sort(
             ds.begin(), ds.end(),
             [](ObjectDetectionDescriptor a, ObjectDetectionDescriptor b) {
                 debug(toString(a));
                 debug(toString(b));
                 return a.rect.height * a.rect.width <= b.rect.height * b.rect.width;
             }
         );

        pds = (PositionalFrameObjectDetectionDescriptor) {
            .position = 0,
            .size = ds.size(),
            .detections = ds.data()
        };

        pds.position = index;
        
        results.push(pds);
    });
    return t;
}
