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
#include "include/dnn.hpp"
#include "include/video.hpp"


using namespace std;
using namespace cv;
using namespace cv::dnn;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        puts("one of parameters is missing");
        puts("program [onnx-model-path] [coco-class-names-path] [video-path]");
        exit(1);
    }

    auto onnxModel = string(argv[1]);
    auto cocoClasses = string(argv[2]);
    auto videoPath = string(argv[3]);
    
    FrameDetections fd;
    
    int retCode = runDetectionsOnVideoONNX(videoPath, onnxModel, cocoClasses, fd);
    if (retCode != 0) {
        puts("Test [runDetectionsOnVideoONNX] failed!");
        exit(1);
    }
    
    retCode = runDetectionsOnVideoONNX("/tmp/blah.jpeg", onnxModel, cocoClasses, fd);
    if (retCode != -1) {
        puts("Test [runDetectionsOnVideoONNX] should have failed with bad video path!");
        exit(1);
    }

    retCode = runDetectionsOnVideoONNX(videoPath, "/tmp/blah.onnx", cocoClasses, fd);
    if (retCode != -1) {
        puts("Test [runDetectionsOnVideoONNX] should have failed with bad ONNX model path!");
        exit(1);
    }

    retCode = runDetectionsOnVideoONNX(videoPath, onnxModel, "/tmp/coco.names", fd);
    if (retCode != -1) {
        puts("Test [runDetectionsOnVideoONNX] should have failed with bad COCO class names path!");
        exit(1);
    }
    
    vector<Mat> frames;
    retCode = readAllFrames(videoPath, frames);
    if (retCode != 0) {
        puts("Test [runDetectionsOnVideoONNX] failed!");
        exit(1);
    }
    
    assert(frames.size() == fd.size);
    puts("test [runDetectionsOnVideoONNX] passed");
}
