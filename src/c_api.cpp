//
//  c_api.cpp
//  c_api
//
//  Created by Denis Makogon on 17.06.2022.
//

#include "includes/dnn.hpp"
#include "includes/drawing.hpp"
#include "includes/classifier.hpp"
#include "includes/etc.hpp"
#include "includes/image.hpp"
#include "includes/to_string.hpp"
#include "includes/files.hpp"

#include "includes/data_types.h"


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

extern "C" const char * PositionalFrameObjectDetectionDescriptor_toString(struct PositionalFrameObjectDetectionDescriptor* PositionalFrameObjectDetectionDescriptor);
const char * PositionalFrameObjectDetectionDescriptor_toString(struct PositionalFrameObjectDetectionDescriptor* PositionalFrameObjectDetectionDescriptor) {
    return stringToChar(toString(*PositionalFrameObjectDetectionDescriptor));
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
                                         const char* imagePath, struct PositionalFrameObjectDetectionDescriptor *pds);
int runClassificationsOnImage(const char* classifierPath,
                              const char* imagePath,
                              struct PositionalFrameObjectDetectionDescriptor *PositionalFrameObjectDetectionDescriptor) {
    return runClassificationsOnImage(string(classifierPath), string(imagePath), *PositionalFrameObjectDetectionDescriptor);
}

extern "C" int processVideoFile(const char* classifierPath,
                                const char* videoFilePath,
                                struct ExportableRectanglesPerFrame* exportableResult);
int processVideoFile(const char* classifierPath,
                     const char* videoFilePath,
                     struct ExportableRectanglesPerFrame* ExportableRectanglesPerFrame) {
    return runClassificationsOnVideo(string(classifierPath), string(videoFilePath), *ExportableRectanglesPerFrame);
}

extern "C" int runDetectionsOnVideo(const char* videoFilePath, const char* modelPath,
                                    const char* modelWeights, const char* cocoaClassesFilePath,
                                    double confidenceThresholdMin,
                                    double confidenceThresholdMax);
int runDetectionsOnVideo(const char* videoFilePath, const char* modelPath,
                         const char* modelWeights, const char* cocoaClassesFilePath,
                         double confidenceThresholdMin,
                         double confidenceThresholdMax) {
    return runDetectionsOnVideo(string(videoFilePath), string(modelPath),
                                string(modelWeights), string(cocoaClassesFilePath),
                                confidenceThresholdMin=confidenceThresholdMin,
                                confidenceThresholdMax=confidenceThresholdMax);
}

extern "C" int runDetectionsOnImage(const char* imagePath, const char* modelPath,
                                    const char* modelWeights, const char* cocoaClassesFilePath,
                                    struct PositionalFrameObjectDetectionDescriptor* PositionalFrameObjectDetectionDescriptor,
                                    double confidenceThresholdMin,
                                    double confidenceThresholdMax);
int runDetectionsOnImage(const char* imagePath, const char* modelPath,
                         const char* modelWeights, const char* cocoaClassesFilePath,
                         struct PositionalFrameObjectDetectionDescriptor* PositionalFrameObjectDetectionDescriptor,
                         double confidenceThresholdMin,
                         double confidenceThresholdMax) {

    return runDetectionsOnImage(string(imagePath), string(modelPath), string(modelWeights),
                                string(cocoaClassesFilePath),
                                *PositionalFrameObjectDetectionDescriptor,
                                confidenceThresholdMin=confidenceThresholdMin,
                                confidenceThresholdMax=confidenceThresholdMax);
}

extern "C" int drawDetectionsOnImage(const char* sourceImagePath,
                                     const char* finalImagePath,
                                     struct PositionalFrameObjectDetectionDescriptor *PositionalFrameObjectDetectionDescriptor,
                                     double scale);
int drawDetectionsOnImage(const char* sourceImagePath,
                          const char* finalImagePath,
                          struct PositionalFrameObjectDetectionDescriptor *PositionalFrameObjectDetectionDescriptor,
                          double scale) {
    return drawDetectionsOnImage(string(sourceImagePath), string(finalImagePath), *PositionalFrameObjectDetectionDescriptor, scale);
}
