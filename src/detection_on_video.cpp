//
//  detection_on_video.cpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 06.07.2022.
//

#include <string>
#include <vector>

#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/dnn.hpp"

#include "include/debug.hpp"
#include "include/video.hpp"
#include "include/files.hpp"
#include "include/dnn.hpp"
#include "include/data_types.h"

using namespace std;
using namespace cv;
using namespace cv::dnn;

int _runDetectionsOnVideo(Net& net, string videoFilePath,
                          string cocoClassesFilePath,
                          FrameDetections& fd,
                         double confidenceThresholdMin=1.0,
                         double confidenceThresholdMax=0.1,
                         int inputSize=640) {
    vector<Mat> frames;
    vector<string> cocoClasses;
    vector<PositionalFrameObjectDetectionDescriptor> detectionsPerFrame;
    int retCode;
    
    retCode = readAllFrames(videoFilePath, frames);
    if ( retCode != 0 ) {
        return retCode;
    }
    
    retCode = readFileToVectorOf(cocoClassesFilePath, cocoClasses);
    if ( retCode != 0 ) {
        return retCode;
    }
    
    for (long i = 0; i < frames.size(); i++ ) {
        vector<ObjectDetectionDescriptor> ds;
        runObjectDetectionsOn(frames[i], net, ds, cocoClasses,
                               confidenceThresholdMin,
                               confidenceThresholdMax,
                               inputSize);
        detectionsPerFrame.push_back({
            .position = static_cast<int>(i),
            .size = ds.size(),
            .detections = ds.data()
        });
    }
    
    fd = (FrameDetections) {
        .size = detectionsPerFrame.size(),
        .frameDetections = detectionsPerFrame.data(),
    };
    
    debug(format("done with _runDetectionsOnVideo, retCode: %d", retCode));
    return retCode;
}

int runDetectionsOnVideoONNX(string videoFilePath, string modelWeights,
                         string cocoClassesFilePath,
                         FrameDetections& fd,
                         double confidenceThresholdMin=0.1,
                         double confidenceThresholdMax=1.0,
                         int inputSize=640) {
    debug("in runDetectionsOnVideo");
    Net net;
    vector<Mat> frames;
    vector<PositionalFrameObjectDetectionDescriptor> detectionsPerFrame;
    vector<string> cocoClasses;
    int retCode = 0;
    
    retCode = setupDNN(modelWeights, net);
    if ( retCode != 0 ) {
        return retCode;
    }

    retCode = _runDetectionsOnVideo(net, videoFilePath, cocoClassesFilePath, fd,
                                    confidenceThresholdMin,
                                    confidenceThresholdMax,
                                    inputSize);
    debug(format("done with runDetectionsOnVideo, retCode: %d", retCode));
    return retCode;
}

int runDetectionsOnVideo(string videoFilePath, string modelPath,
                         string modelWeights, string cocoClassesFilePath,
                         FrameDetections& fd,
                         double confidenceThresholdMin=0.1,
                         double confidenceThresholdMax=1.0,
                         int inputSize=640) {
    debug("in runDetectionsOnVideo");
    Net net;
    vector<Mat> frames;
    vector<PositionalFrameObjectDetectionDescriptor> detectionsPerFrame;
    vector<string> cocoClasses;

    int retCode = 0;
    retCode = setupDNN(modelPath, modelWeights, net);
    if ( retCode != 0 ) {
        return retCode;
    }

    retCode = _runDetectionsOnVideo(net, videoFilePath, cocoClassesFilePath, fd,
                                    confidenceThresholdMin,
                                    confidenceThresholdMax,
                                    inputSize);
    
    debug(format("done with runDetectionsOnVideo, retCode: %d", retCode));
    return retCode;
}
