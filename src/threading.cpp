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

#include "opencv2/core/mat.hpp"
#include "opencv2/dnn.hpp"

#include "include/debug.hpp"
#include "include/dnn.hpp"
#include "include/export.hpp"
#include "include/to_string.hpp"


using namespace std;
using namespace cv;
using namespace cv::dnn;

thread create_frame_detection_tasks(Net& net, Mat& frame, int index,
                                    vector<string>& cocoClasses,
                                    vector<PositionalFrameObjectDetectionDescriptor>& results,
                                    double confidenceThresholdMin=0.1,
                                    double confidenceThresholdMax=1.0,
                                    int inputSize=640) {
    debug("in create_frame_detection_tasks");
    thread t([&net, &frame, &index, &cocoClasses,
               &confidenceThresholdMin,
               &confidenceThresholdMax, &results, &inputSize] () {
        debug("in threaded task");
        vector<ObjectDetectionDescriptor> ds;
        _runObjectDetectionsOn(frame, net, ds, cocoClasses,
                               confidenceThresholdMin,
                               confidenceThresholdMax,
                               inputSize);
        
        results.push_back({
            .position = index,
            .size = ds.size(),
            .detections = ds.data(),
        });
        debug("done with threaded task");
    });
    debug("done with create_frame_detection_tasks");
    return t;
}
