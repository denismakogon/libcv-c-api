//
//  classifier.cpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//

#include <vector>
#include <string>
#include <stdio.h>

#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

#include "opencv2/videoio.hpp"

#include "opencv2/dnn.hpp"
#include "opencv2/objdetect.hpp"

#include "includes/data_types.h"

#include "includes/debug.hpp"
#include "includes/etc.hpp"
#include "includes/image.hpp"
#include "includes/files.hpp"
#include "includes/export.hpp"
#include "includes/video.hpp"

using namespace std;
using namespace cv;
using namespace cv::samples;

/*-----------------------------------------------------------------------*/
/*--------------------------Classfiers API-------------------------------*/
/*-----------------------------------------------------------------------*/

void prepareImageForClassification(Mat& img, Mat& result) {
    debug("in prepareImageForClassification");
    Mat blurred, dilated, kernel;
    GaussianBlur(img, blurred, Size(5, 5), 0);
    dilate(blurred, dilated, Mat(), Point(-1, -1));
    kernel = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));
    morphologyEx(dilated, result, MORPH_CLOSE, kernel);
    debug("done with prepareImageForClassification");
}

void runClassifier(CascadeClassifier& cascade, Mat& source, Mat& result, vector<Rect>& detections) {
    debug("in runClassifier");
    source.copyTo(result);

    Mat preprocessedSource;
    prepareImageForClassification(source, preprocessedSource);

    cascade.detectMultiScale(preprocessedSource, detections, 1.1, 1);
    debug("done with runClassifier");
}

int runClassification(string classifierPath, string imagePath, vector<Rect>& results) {
    debug("in runClassification");
    CascadeClassifier cascade;
    int retCode = 0;
    try {
        retCode = cascade.load(classifierPath);
        debug("done reading classifier from a file" + classifierPath + format("%d", retCode));
        if (retCode != 1) {
            return retCode;
        }
    } catch (Exception& ex) {
        debug(ex.what());
        return -1;
    }

    Mat source, finalImg;
    retCode = readImageFile(source, imagePath, IMREAD_COLOR);
    if (retCode != 0) {
        return retCode;
    }

    runClassifier(cascade, source, finalImg, results);
    debug(format("done with runClassification, retCode: %d", retCode));
    return retCode;
}

int runClassificationsOnImage(string classifierPath, string imagePath, PositionalFrameObjectDetectionDescriptor& pds) {
    debug("in runClassificationsOnImage");
    vector<Rect> detections;
    int retCode = 0;
    
    retCode = runClassification(string(classifierPath), string(imagePath), detections);
    if ( retCode != 0 ) {
        return retCode;
    }
    
    exportVectorOf(detections, pds);
    debug(format("done with runClassificationsOnImage, retCode: %d", retCode));
    return retCode;
}

int runClassificationsOnVideo(string classifierPath, string videoFilePath,
                              vector<ExportableRectangles>& result) {
    debug("in processVideoFile");
    CascadeClassifier cascade;
    if ( !cascade.load(findFile(classifierPath)) ) {
        debug("classifier not found!");
        return -1;
    };
    
    vector<Mat> frames;
    int retCode = 0;
    
    retCode = readAllFrames(videoFilePath, frames);
    if (retCode != 0) {
        return retCode;
    }

    Mat currentFrame, finalImg;
    for (long i = 0; i < frames.size(); i++) {
        vector<Rect> detections;
        runClassifier(cascade, frames[i], finalImg, detections);
        ExportableRectangle* res = new ExportableRectangle[detections.size()];

        exportVectorOf(detections, res);
        result.push_back((ExportableRectangles) {
            .array = res,
            .size = detections.size()
        });
    }
    debug(format("done with processVideoFile, retCode: %d", retCode));
    return retCode;
}

int runClassificationsOnVideo(string classifierPath, string videoFilePath,
                              ExportableRectanglesPerFrame& exportableResult) {
    debug("in processVideoFile");
    vector<ExportableRectangles> result;
    int retCode = 0;
    retCode = runClassificationsOnVideo(string(classifierPath), string(videoFilePath), result);
    if ( retCode != 0 ) {
        return retCode;
    }
    exportVectorOf(result, exportableResult);
    debug(format("done with processVideoFile, retCode: %d", retCode));
    return retCode;
}
