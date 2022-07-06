//
//  c_api.cpp
//  c_api
//
//  Created by Denis Makogon on 17.06.2022.
//

#include "include/drawing.hpp"
#include "include/classifier.hpp"
#include "include/etc.hpp"
#include "include/image.hpp"
#include "include/to_string.hpp"
#include "include/files.hpp"
#include "include/detection_on_image.hpp"
#include "include/detection_on_video.hpp"

#include "include/data_types.h"


using namespace std;

/*-----------------------------------------------------------------------*/
/*---------------------------C API collection----------------------------*/
/*-----------------------------------------------------------------------*/

extern "C" const char* ExportableRectangle_toString(struct ExportableRectangle *ExportableRectangle);
const char* ExportableRectangle_toString(struct ExportableRectangle *ExportableRectangle) {
    return stringToChar(toString(*ExportableRectangle));
}

extern "C" const char* ObjectDetectionDescriptor_toString(struct ObjectDetectionDescriptor *ObjectDetectionDescriptor);
const char* ObjectDetectionDescriptor_toString(struct ObjectDetectionDescriptor *ObjectDetectionDescriptor) {
    return stringToChar(toString(*ObjectDetectionDescriptor));
}

extern "C" const char * PositionalFrameObjectDetectionDescriptor_toString(struct PositionalFrameObjectDetectionDescriptor* positionalFrameObjectDetectionDescriptor);
const char * PositionalFrameObjectDetectionDescriptor_toString(struct PositionalFrameObjectDetectionDescriptor* positionalFrameObjectDetectionDescriptor) {
    return stringToChar(toString(*positionalFrameObjectDetectionDescriptor));
}

extern "C" int imageToMatrix(const char* imagePath,
                             int option,
                             struct ExportableMat *exMat);
int imageToMatrix(const char* imagePath,
                  int option, struct
                  ExportableMat *ExportableMat) {
    return imageToMatrix(string(imagePath), option, *ExportableMat);
}

extern "C" int runClassificationsOnImage(const char* classifierPath,
                                         const char* imagePath, struct PositionalFrameObjectDetectionDescriptor *positionalFrameObjectDetectionDescriptor);
int runClassificationsOnImage(const char* classifierPath,
                              const char* imagePath,
                              struct PositionalFrameObjectDetectionDescriptor *positionalFrameObjectDetectionDescriptor) {
    return runClassificationsOnImage(string(classifierPath), string(imagePath), *positionalFrameObjectDetectionDescriptor);
}

extern "C" int processVideoFile(const char* classifierPath,
                                const char* videoFilePath,
                                struct ExportableRectanglesPerFrame* exportableResult);
int processVideoFile(const char* classifierPath,
                     const char* videoFilePath,
                     struct ExportableRectanglesPerFrame* ExportableRectanglesPerFrame) {
    return runClassificationsOnVideo(string(classifierPath), string(videoFilePath), *ExportableRectanglesPerFrame);
}

extern "C" int runDetectionsOnVideo(const char* videoFilePath,
                                    const char* modelPath,
                                    const char* modelWeights,
                                    const char* cocoClassesFilePath,
                                    double confidenceThresholdMin,
                                    double confidenceThresholdMax);
int runDetectionsOnVideo(const char* videoFilePath, const char* modelPath,
                         const char* modelWeights, const char* cocoClassesFilePath,
                         struct FrameDetections* frameDetections,
                         double confidenceThresholdMin,
                         double confidenceThresholdMax) {
    return runDetectionsOnVideo(string(videoFilePath), string(modelPath),
                                string(modelWeights), string(cocoClassesFilePath),
                                *frameDetections,
                                confidenceThresholdMin,
                                confidenceThresholdMax);
}

extern "C" int runDetectionsOnVideoONNX(const char* videoFilePath,
                                    const char* modelWeights,
                                    const char* cocoClassesFilePath,
                                    double confidenceThresholdMin,
                                    double confidenceThresholdMax);
int runDetectionsOnVideoONNX(const char* videoFilePath,
                             const char* modelWeights,
                             const char* cocoClassesFilePath,
                             struct FrameDetections* frameDetections,
                             double confidenceThresholdMin,
                             double confidenceThresholdMax) {
    return runDetectionsOnVideoONNX(string(videoFilePath),
                                string(modelWeights),
                                string(cocoClassesFilePath),
                                *frameDetections,
                                confidenceThresholdMin,
                                confidenceThresholdMax);
}

extern "C" int runDetectionsOnImage(const char* imagePath, const char* modelPath,
                                    const char* modelWeights, const char* cocoClassesFilePath,
                                    struct PositionalFrameObjectDetectionDescriptor* positionalFrameObjectDetectionDescriptor,
                                    double confidenceThresholdMin,
                                    double confidenceThresholdMax,
                                    int inputSize);
int runDetectionsOnImage(const char* imagePath, const char* modelPath,
                         const char* modelWeights, const char* cocoClassesFilePath,
                         struct PositionalFrameObjectDetectionDescriptor* positionalFrameObjectDetectionDescriptor,
                         double confidenceThresholdMin,
                         double confidenceThresholdMax,
                         int inputSize) {

    return runDetectionsOnImage(string(imagePath),
                                string(modelPath),
                                string(modelWeights),
                                string(cocoClassesFilePath),
                                *positionalFrameObjectDetectionDescriptor,
                                confidenceThresholdMin,
                                confidenceThresholdMax,
                                inputSize);
}

extern "C" int runDetectionsOnImageONNX(const char* imagePath,
                                        const char* modelWeights,
                                        const char* cocoClassesFilePath,
                                        struct PositionalFrameObjectDetectionDescriptor* positionalFrameObjectDetectionDescriptor,
                                        double confidenceThresholdMin,
                                        double confidenceThresholdMax,
                                        int inputSize);
int runDetectionsOnImageONNX(const char* imagePath,
                             const char* modelWeights,
                             const char* cocoClassesFilePath,
                             struct PositionalFrameObjectDetectionDescriptor* positionalFrameObjectDetectionDescriptor,
                             double confidenceThresholdMin,
                             double confidenceThresholdMax,
                             int inputSize) {

    return runDetectionsOnImageONNX(string(imagePath),
                                    string(modelWeights),
                                    string(cocoClassesFilePath),
                                    *positionalFrameObjectDetectionDescriptor,
                                    confidenceThresholdMin,
                                    confidenceThresholdMax,
                                    inputSize);
}


extern "C" int drawDetectionsOnImage(const char* sourceImagePath,
                                     const char* finalImagePath,
                                     struct PositionalFrameObjectDetectionDescriptor *positionalFrameObjectDetectionDescriptor,
                                     double scale);
int drawDetectionsOnImage(const char* sourceImagePath,
                          const char* finalImagePath,
                          struct PositionalFrameObjectDetectionDescriptor *positionalFrameObjectDetectionDescriptor,
                          double scale) {
    return drawDetectionsOnImage(string(sourceImagePath), string(finalImagePath), *positionalFrameObjectDetectionDescriptor, scale);
}
