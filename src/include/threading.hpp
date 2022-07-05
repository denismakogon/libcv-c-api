//
//  threading.hpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 04.07.2022.
//

#ifndef threading_hpp
#define threading_hpp

#include <stdio.h>
#include <thread>
#include <string>
#include <vector>
#include <deque>

#include "opencv2/core/mat.hpp"
#include "opencv2/dnn.hpp"

using namespace std;
using namespace cv;
using namespace cv::dnn;

thread create_frame_detection_tasks(Net& net, Mat& frame, int index,
                                    vector<string>& cocoClasses,
                                    deque<PositionalFrameObjectDetectionDescriptor>& results,
                                    double confidenceThresholdMin=0.1,
                                    double confidenceThresholdMax=1.0,
                                    int inputSize=640);

#endif /* threading_hpp */
