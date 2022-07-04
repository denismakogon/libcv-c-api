//
//  dnn.hpp
//  c_api
//
//  Created by Denis Makogon on 21.06.2022.
//

#ifndef cpp_api_hpp
#define cpp_api_hpp

#include <string>
#include <vector>

#include "opencv2/core/mat.hpp"
#include "opencv2/dnn.hpp"

#include "include/data_types.h"


using namespace std;
using namespace cv;
using namespace cv::dnn;

void runObjectDetectionsOn(Mat& img, Net& net, vector<ObjectDetectionDescriptor>& ds,
                            vector<string>& cocoClasses,
                            double confidenceThresholdMin=0.1,
                            double confidenceThresholdMax=1.0);

int runDetectionsOnVideo(string videoFilePath, string modelPath,
                         string modelWeights, string cocoClassesFilePath,
                         FrameDetections& fd,
                         double confidenceThresholdMin=0.1,
                         double confidenceThresholdMax=1.0);

int runDetectionsOnVideoONNX(string videoFilePath, string modelWeights,
                         string cocoClassesFilePath,
                         FrameDetections& fd,
                         double confidenceThresholdMin=0.1,
                         double confidenceThresholdMax=1.0);

int runDetectionsOnImage(string imagePath, string modelPath, string modelWeights,
                         string cocoClassesFilePath,
                         PositionalFrameObjectDetectionDescriptor& pds,
                         double confidenceThresholdMin=0.1,
                         double confidenceThresholdMax=1.0,
                         int inputSize=640);

int runDetectionsOnImageONNX(string imagePath, string modelWeights,
                             string cocoClassesFilePath,
                             PositionalFrameObjectDetectionDescriptor& pds,
                             double confidenceThresholdMin=0.1,
                             double confidenceThresholdMax=1.0,
                             int inputSize=640);

int runDetectionsOnImageONNX(string imagePath, string modelWeights,
                             string cocoClassesFilePath,
                             vector<ObjectDetectionDescriptor>& ds,
                             double confidenceThresholdMin=0.1,
                             double confidenceThresholdMax=1.0,
                             int inputSize=640);
// service functions

void _runObjectDetectionsOn(Mat& img, Net& net, vector<ObjectDetectionDescriptor>& ds,
                           vector<string>& cocoClasses,
                           double confidenceThresholdMin,
                           double confidenceThresholdMax,
                           int inputSize);

#endif /* cpp_api_hpp */
