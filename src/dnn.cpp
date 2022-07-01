//
//  dnn.cpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//

#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

#include "opencv2/videoio.hpp"

#include "opencv2/dnn.hpp"
#include "opencv2/objdetect.hpp"

#include "include/data_types.h"

#include "include/debug.hpp"
#include "include/etc.hpp"
#include "include/export.hpp"
#include "include/image.hpp"
#include "include/video.hpp"
#include "include/files.hpp"

#include <iostream>
#include <cstdio>
#include <iterator>
#include <fstream>


using namespace std;
using namespace cv;
using namespace cv::samples;
using namespace cv::dnn;


/*-----------------------------------------------------------------------*/
/*-------------------------------DNN API---------------------------------*/
/*-----------------------------------------------------------------------*/

int setupDNN(string modelPath, string modelWeights, Net& net,
             int backend=DNN_BACKEND_DEFAULT,
             int target=DNN_TARGET_CPU) {
    debug("in setupDNN");
    try {
        net = readNetFromDarknet(findFile(modelPath), findFile(modelWeights));
        net.setPreferableBackend(backend);
        net.setPreferableTarget(target);
    } catch (Exception& ex) {
        debug(ex.what());
        return -1;
    }
    debug(format("done with setupDNN, retCode: %d", 0));
    return 0;
}


void inputPreprocess(const Mat& frame, Net& net, Size inpSize, float scale,
                       const Scalar& mean, bool swapRB) {
    debug("in inputPreprocess");
    static Mat blob;
    if (inpSize.width <= 0) inpSize.width = frame.cols;
    if (inpSize.height <= 0) inpSize.height = frame.rows;
    blobFromImage(frame, blob, 1.0, inpSize, Scalar(), swapRB, false, CV_8U);
    net.setInput(blob, "", scale, mean);
    if (net.getLayer(0)->outputNameToIndex("im_info") != -1)  // Faster-RCNN or R-FCN
    {
        resize(frame, frame, inpSize);
        Mat imInfo = (Mat_<float>(1, 3) << inpSize.height, inpSize.width, 1.6f);
        net.setInput(imInfo, "im_info");
    }
    debug("done with inputPreprocess");
}

void formatDetections(Mat& frame, vector<Mat>& outs, Net& net, vector<ObjectDetectionDescriptor>& ds,
                      vector<string>& cocoaClasses,
                      double confidenceThresholdMax=1.0,
                      double confidenceThresholdMin=0.1,
                      int backend=DNN_BACKEND_DEFAULT) {
    debug("in formatDetections");
    static std::vector<int> outLayers = net.getUnconnectedOutLayers();
    static std::string outLayerType = net.getLayer(outLayers[0])->type;

    if (outLayerType == "DetectionOutput") {
        for (size_t k = 0; k < outs.size(); k++) {
            float* data = (float*)outs[k].data;
            for (size_t i = 0; i < outs[k].total(); i += 7) {
                float confidence = data[i + 2];
                int classID = (int)(data[i + 1]) - 1;
                
                checkElementByIndexAt(cocoaClasses, classID);
                bool isMatch =
                    (confidence > confidenceThresholdMin && confidence < confidenceThresholdMax) && checkElementByIndexAt(cocoaClasses, classID);
                
                if (isMatch) {
                    int left   = (int)data[i + 3];
                    int top    = (int)data[i + 4];
                    int right  = (int)data[i + 5];
                    int bottom = (int)data[i + 6];
                    int width  = right - left + 1;
                    int height = bottom - top + 1;
                    if (width <= 2 || height <= 2) {
                        left   = (int)(data[i + 3] * frame.cols);
                        top    = (int)(data[i + 4] * frame.rows);
                        right  = (int)(data[i + 5] * frame.cols);
                        bottom = (int)(data[i + 6] * frame.rows);
                        width  = right - left + 1;
                        height = bottom - top + 1;
                    }
                    
                    ds.push_back((ObjectDetectionDescriptor) {
                        .className = strdup(cocoaClasses[classID].c_str()),
                        .confidence = confidence,
                        .rect = (ExportableRectangle) {
                            .x0 = left,
                            .y0 = top,
                            .x1 = left + width-1,
                            .y1 = top + height-1,
                            .width = width,
                            .height = height
                        }
                    });
                }
            }
        }
    } else if (outLayerType == "Region") {
        for (long i = 0; i < outs.size(); ++i) {
            float* data = (float*)outs[i].data;
            for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) {
                Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
                Point classIdPoint;
                double confidence;
                minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);

                bool isMatch =
                    (confidence > confidenceThresholdMin && confidence < confidenceThresholdMax) && checkElementByIndexAt(cocoaClasses, classIdPoint.x);

                if (isMatch) {
                    int centerX = (int)(data[0] * frame.cols);
                    int centerY = (int)(data[1] * frame.rows);
                    int width = (int)(data[2] * frame.cols);
                    int height = (int)(data[3] * frame.rows);
                    
                    int left = centerX - width / 2;
                    int top = centerY - height / 2;

                    ds.push_back((ObjectDetectionDescriptor) {
                        .className = strdup(cocoaClasses[classIdPoint.x].c_str()),
                        .confidence = confidence,
                        .rect = (ExportableRectangle) {
                            .x0 = left,
                            .y0 = top,
                            .x1 = left + width-1,
                            .y1 = top + height-1,
                            .width = width,
                            .height = height
                        }
                    });
                }
            }
        }
    } else
        CV_Error(Error::StsNotImplemented, "Unknown output layer type: " + outLayerType);

    debug("done with formatDetections");
}

void runtObjectDetectionsOn(Mat& img, Net& net, vector<ObjectDetectionDescriptor>& ds,
                            vector<string>& cocoaClasses,
                            double confidenceThresholdMax=1.0,
                            double confidenceThresholdMin=0.1) {
    
    debug("in runtObjectDetectionsOn");
    int inputSize = 320;
    vector<Mat> outputs;

    inputPreprocess(img, net, Size(inputSize, inputSize), (float) 1/255, Scalar(0, 0, 0), false);
    net.forward(outputs, net.getUnconnectedOutLayersNames());
    
    formatDetections(img, outputs, net, ds, cocoaClasses,
                     confidenceThresholdMax=confidenceThresholdMax,
                     confidenceThresholdMin=confidenceThresholdMin);
    debug("done with runtObjectDetectionsOn");
}

int runDetectionsOnImage(string imagePath, string modelPath, string modelWeights,
                         string cocoaClassesFilePath,
                         PositionalFrameObjectDetectionDescriptor& pds,
                         double confidenceThresholdMin=0.1,
                         double confidenceThresholdMax=1.0) {
    debug("in runDetectionsOn");
    dnn::Net net;
    Mat frame;
    vector<ObjectDetectionDescriptor> ds;

    int retCode = 0;
    retCode = readImageFile(frame, imagePath, IMREAD_COLOR);
    if ( retCode != 0 ) {
        return retCode;
    }
    
    retCode = setupDNN(modelPath, modelWeights, net);
    if ( retCode != 0 ) {
        return retCode;
    }
    
    vector<string> cocoaClasses;
    retCode = readFileToVectorOf(cocoaClassesFilePath, cocoaClasses);
    if ( retCode != 0 ) {
        return retCode;
    }
    
    runtObjectDetectionsOn(frame, net, ds, cocoaClasses,
                           confidenceThresholdMax=confidenceThresholdMax,
                           confidenceThresholdMin=confidenceThresholdMin);

    sort(
         ds.begin(), ds.end(),
         [](ObjectDetectionDescriptor a, ObjectDetectionDescriptor b) {
             return a.rect.x0 <= b.rect.x0;
         }
     );
    pds = (PositionalFrameObjectDetectionDescriptor) {
        .position = 0,
        .size = ds.size(),
        .detections = ds.data()
    };

    debug(format("done with runDetectionsOn, retCode: %d", retCode));
    return retCode;
}

int runDetectionsOnVideo(string videoFilePath, string modelPath,
                         string modelWeights, string cocoaClassesFilePath,
                         double confidenceThresholdMax=1.0,
                         double confidenceThresholdMin=0.1) {
    debug("in runDetectionsOnVideo");
    dnn::Net net;
    vector<Mat> frames;
    vector<PositionalFrameObjectDetectionDescriptor> detectionsPerFrame;
    vector<string> cocoaClasses;

    int retCode = 0;
    retCode = readAllFrames(videoFilePath, frames);
    if ( retCode != 0 ) {
        return retCode;
    }
    retCode = setupDNN(modelPath, modelWeights, net);
    if ( retCode != 0 ) {
        return retCode;
    }
    
    retCode = readFileToVectorOf(cocoaClassesFilePath, cocoaClasses);
    if ( retCode != 0 ) {
        return retCode;
    }
    
    for (long i = 0; i < frames.size(); i++ ) {
        vector<ObjectDetectionDescriptor> ds;
        runtObjectDetectionsOn(frames[i], net, ds, cocoaClasses,
                               confidenceThresholdMax=confidenceThresholdMax,
                               confidenceThresholdMin=confidenceThresholdMin);
        detectionsPerFrame.push_back((PositionalFrameObjectDetectionDescriptor) {
            .position = static_cast<int>(i),
            .size = ds.size(),
            .detections = ds.data()
        });
    }
    debug(format("done with runDetectionsOnVideo, retCode: %d", retCode));
    return retCode;
}
