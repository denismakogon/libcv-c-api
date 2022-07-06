//
//  detection_on_image.hpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 06.07.2022.
//

#ifndef detection_on_image_hpp
#define detection_on_image_hpp

#include <string>
#include <vector>

#include "opencv2/core/mat.hpp"
#include "opencv2/dnn.hpp"

using namespace std;
using namespace cv;
using namespace cv::dnn;


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

#endif /* detection_on_image_hpp */
