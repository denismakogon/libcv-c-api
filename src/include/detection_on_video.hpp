//
//  detection_on_video.hpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 06.07.2022.
//

#ifndef detection_on_video_hpp
#define detection_on_video_hpp

#include <string>
#include <vector>

#include "opencv2/core/mat.hpp"
#include "opencv2/dnn.hpp"

#include "include/data_types.h"

using namespace std;
using namespace cv;
using namespace cv::dnn;


int runDetectionsOnVideo(string videoFilePath, string modelPath,
                         string modelWeights, string cocoClassesFilePath,
                         FrameDetections& fd,
                         double confidenceThresholdMin=0.1,
                         double confidenceThresholdMax=1.0,
                         int inputSize=640);

int runDetectionsOnVideoONNX(string videoFilePath, string modelWeights,
                         string cocoClassesFilePath,
                         FrameDetections& fd,
                         double confidenceThresholdMin=0.1,
                         double confidenceThresholdMax=1.0,
                         int inputSize=640);

#endif /* detection_on_video_hpp */
