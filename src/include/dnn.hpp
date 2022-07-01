//
//  dnn.hpp
//  c_api
//
//  Created by Denis Makogon on 21.06.2022.
//

#ifndef cpp_api_hpp
#define cpp_api_hpp

#include <string>

#include "opencv2/core/mat.hpp"

#include "include/data_types.h"


using namespace std;
using namespace cv;

int runDetectionsOnVideo(string videoFilePath, string modelPath,
                         string modelWeights, string cocoaClassesFilePath,
                         double confidenceThresholdMax=1.0,
                         double confidenceThresholdMin=0.1);

int runDetectionsOnImage(string imagePath, string modelPath, string modelWeights,
                         string cocoaClassesFilePath,
                         PositionalFrameObjectDetectionDescriptor& pds,
                         double confidenceThresholdMax=1.0,
                         double confidenceThresholdMin=0.1);

#endif /* cpp_api_hpp */
