//
//  test_dnn.cpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 03.07.2022.
//

#include <string>

#include "opencv2/core/mat.hpp"
#include "opencv2/dnn.hpp"

#include "include/data_types.h"
#include "include/detection_on_image.hpp"
#include "include/to_string.hpp"


using namespace std;
using namespace cv;
using namespace cv::dnn;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        puts("one of parameters is missing");
        puts("program [onnx-model-path] [coco-class-names-path] [image-path]");
        exit(1);
    }

    auto onnxModel = string(argv[1]);
    auto cocoClasses = string(argv[2]);
    auto imagePath = string(argv[3]);
    
    PositionalFrameObjectDetectionDescriptor pds;
    vector<ObjectDetectionDescriptor> ds;
    
    int retCode = runDetectionsOnImageONNX(imagePath, onnxModel, cocoClasses, pds);
    if (retCode != 0) {
        puts("Test [runDetectionsOnImageONNX] failed!");
        exit(1);
    }
    assert(pds.size > 0);
    assert(pds.detections != 0);

    retCode = runDetectionsOnImageONNX("/tmp/blah.jpeg", onnxModel, cocoClasses, ds);
    if (retCode != -1) {
        puts("Test [runDetectionsOnImageONNX] should have failed with bad image path!");
        exit(1);
    }

    retCode = runDetectionsOnImageONNX(imagePath, "/tmp/dummy.onnx", cocoClasses, ds);
    if (retCode != -1) {
        puts("Test [runDetectionsOnImageONNX] should have failed with bad ONNX model path!");
        exit(1);
    }

    retCode = runDetectionsOnImageONNX(imagePath, onnxModel, "/tmp/dummy.coco.names", ds);
    if (retCode != -1) {
        puts("Test [runDetectionsOnImageONNX] should have failed with bad COCO class names path!");
        exit(1);
    }
    puts("test [runDetectionsOnImageONNX] passed");

}
