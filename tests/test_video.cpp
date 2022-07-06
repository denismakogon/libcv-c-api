//
//  test_video.cpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 01.07.2022.
//

#include <stdio.h>
#include <string>
#include <vector>

#include "include/video.hpp"

#include "opencv2/core/mat.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        puts("video path parameter is missing");
        puts("program [video-path] [image-path]");
        exit(1);
    }

    auto videoFile = string(argv[1]);
    auto imagePath = string(argv[2]);
    vector<Mat> frames;
    
    int retCode = readAllFrames(videoFile, frames);
    if (retCode != 0) {
        puts("Test [read existing video] failed!");
        exit(retCode);
    }
    
    retCode = readAllFrames("/tmp/bad-video.avi", frames);
    if (retCode != -1) {
        puts("Test [read existing video] should have failed!");
        exit(1);
    }
    
    vector<Mat> newframes;
    retCode = readAllFrames(imagePath, newframes);
    if (retCode != 0) {
        puts("Test [read existing video] should have failed!");
        exit(retCode);
    }
    
    assert(newframes.size() == 1);
    assert(frames.size() > 0);
    
    puts("tests [readAllFrames] passed");
}
