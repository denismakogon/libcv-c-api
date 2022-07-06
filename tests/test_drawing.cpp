//
//  test_drawing.cpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 04.07.2022.
//

#include "stdio.h"

#include <string>
#include <fstream>

#include "include/data_types.h"

#include "include/detection_on_image.hpp"
#include "include/drawing.hpp"


inline bool file_exists(string name) {
    ifstream f(name.c_str());
    return f.good();
}


int main (int argc, char* argv[]) {
    if (argc < 4) {
        puts("one of parameters is missing");
        puts("program [onnx-model-path] [coco-class-names-path] [image-path]");
        exit(1);
    }
    auto onnxModel = string(argv[1]);
    auto cocoClasses = string(argv[2]);
    auto imagePath = string(argv[3]);
    auto finalImagePath = imagePath + ".final.jpeg";
    
    PositionalFrameObjectDetectionDescriptor pds;
    vector<ObjectDetectionDescriptor> ds;
    
    int retCode = runDetectionsOnImageONNX(imagePath, onnxModel, cocoClasses, pds);
    if (retCode != 0) {
        puts("Test [runDetectionsOnImageONNX for drawDetectionsOnImage] failed!");
        exit(retCode);
    }
    assert(pds.size > 0);
    assert(pds.detections != 0);

    retCode = drawDetectionsOnImage(imagePath, finalImagePath, pds);
    if (retCode != 1) {
        puts("Test [drawDetectionsOnImage] failed!");
        exit(1);
    }
    
    assert(true == file_exists(finalImagePath));
    
    remove(finalImagePath.c_str());
    
    puts("Test [runDetectionsOnImageONNX for drawDetectionsOnImage] passed!");
}
