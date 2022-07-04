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
    if (argc < 2) {
        puts("video path parameter is missing");
        puts("program [video-path]");
        exit(1);
    }

    auto videoFile = string(argv[1]);
    vector<Mat> frames;
    
    int retCode = readAllFrames(videoFile, frames);
    if (retCode != 0) {
        puts("Test [read existing video] failed!");
        exit(1);
    }
    
    retCode = readAllFrames("/tmp/bad-video.avi", frames);
    if (retCode != -1) {
        puts("Test [read existing video] should have failed!");
        exit(1);
    }
    
    assert(frames.size() > 0);
    puts("tests [readAllFrames] passed");
}
