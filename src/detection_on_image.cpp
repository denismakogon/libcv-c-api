//
//  detection_on_image.cpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 06.07.2022.
//
#include <string>
#include <vector>

#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/dnn.hpp"

#include "include/debug.hpp"
#include "include/etc.hpp"
#include "include/export.hpp"
#include "include/image.hpp"
#include "include/files.hpp"

#include "include/dnn.hpp"

#include "include/data_types.h"

using namespace std;
using namespace cv;
using namespace cv::dnn;

int _runDetectionsOnImage(Net& net, string imagePath, string cocoClassesFilePath,
                          vector<ObjectDetectionDescriptor>& ds,
                          double confidenceThresholdMin=0.1,
                          double confidenceThresholdMax=1.0,
                          int inputSize=640) {
    debug("in _runDetectionsOnImage");
    Mat frame;
    int retCode;
    
    retCode = readImageFile(frame, imagePath, IMREAD_COLOR);
    if ( retCode != 0 ) {
        return retCode;
    }

    vector<string> cocoClasses;
    retCode = readFileToVectorOf(cocoClassesFilePath, cocoClasses);
    if ( retCode != 0 ) {
        return retCode;
    }
    
    runObjectDetectionsOn(frame, net, ds, cocoClasses,
                          confidenceThresholdMin,
                          confidenceThresholdMax,
                          inputSize);

    debug(format("in _runDetectionsOnImage, detections number = %lu", ds.size()));

    debug(format("done with _runDetectionsOnImage, retCode: %d", retCode));
    return retCode;
}

int runDetectionsOnImageONNX(string imagePath, string modelWeights,
                             string cocoClassesFilePath,
                             vector<ObjectDetectionDescriptor>& ds,
                             double confidenceThresholdMin=0.1,
                             double confidenceThresholdMax=1.0,
                             int inputSize=640) {
    debug("in runDetectionsOnImageONNX");
    Net net;
    Mat frame;
    
    int retCode;
    retCode = setupDNN(modelWeights, net);
    if ( retCode != 0 ) {
        return retCode;
    }
    
    retCode = _runDetectionsOnImage(net, imagePath, cocoClassesFilePath, ds,
                                    confidenceThresholdMin,
                                    confidenceThresholdMax,
                                    inputSize);
      
    debug(format("done with runDetectionsOnImageONNX, retCode: %d", retCode));
    return retCode;
}

int runDetectionsOnImageONNX(string imagePath, string modelWeights,
                             string cocoClassesFilePath,
                             PositionalFrameObjectDetectionDescriptor& pds,
                             double confidenceThresholdMin=0.1,
                             double confidenceThresholdMax=1.0,
                             int inputSize=640) {
    debug("in runDetectionsOnImageONNX");
    Net net;
    Mat frame;
    vector<ObjectDetectionDescriptor> ds;
    
    int retCode = runDetectionsOnImageONNX(imagePath, modelWeights, cocoClassesFilePath, ds,
                                           confidenceThresholdMin,
                                           confidenceThresholdMax,
                                           inputSize);
    
    ObjectDetectionDescriptor arr[ds.size()];
    copy(ds.begin(), ds.end(), arr);

    pds = {};
    pds.size = ds.size();
    pds.position = 0;
    pds.detections = arr;
    
    debug(format("done with runDetectionsOnImageONNX, retCode: %d", retCode));
    return retCode;
}

int runDetectionsOnImage(string imagePath, string modelPath, string modelWeights,
                         string cocoClassesFilePath,
                         PositionalFrameObjectDetectionDescriptor& pds,
                         double confidenceThresholdMin=0.1,
                         double confidenceThresholdMax=1.0,
                         int inputSize=320) {
    debug("in runDetectionsOnImage");
    Net net;
    Mat frame;
    vector<ObjectDetectionDescriptor> ds;

    int retCode = 0;
    
    retCode = setupDNN(modelPath, modelWeights, net);
    if ( retCode != 0 ) {
        return retCode;
    }
    
    retCode = _runDetectionsOnImage(net, imagePath, cocoClassesFilePath, ds,
                                    confidenceThresholdMin,
                                    confidenceThresholdMax,
                                    inputSize);

    pds = {};
    pds.size = ds.size();
    pds.position = 0;
    pds.detections = ds.data();

    debug(format("done with runDetectionsOnImage, retCode: %d", retCode));
    return retCode;
}
