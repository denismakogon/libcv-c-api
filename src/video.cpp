//
//  video.cpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//
#include <string>
#include <vector>

#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

#include "opencv2/videoio.hpp"

#include "include/debug.hpp"

using namespace std;
using namespace cv;
using namespace cv::samples;

/*-----------------------------------------------------------------------*/
/*-----------------------------Video API---------------------------------*/
/*-----------------------------------------------------------------------*/

int readAllFrames(string videoFilePath, vector<Mat>& frames) {
    debug("in readAllFrames");
    VideoCapture capture;
    try {
        capture = VideoCapture(findFile(videoFilePath));
        if ( !capture.isOpened() ) {
            return -1;
        }
    } catch (Exception& ex) {
        debug(ex.what());
        return -1;
    }

    int frameCount = capture.get(CAP_PROP_FRAME_COUNT);
    
    Mat currentFrame;
    for (int i = 0; i < frameCount; i ++) {
        capture >> currentFrame;
        if (currentFrame.empty()) {
            break;
        }
        frames.push_back(currentFrame);
    }
    debug(format("done with readAllFrames, retCode: %d", 0));
    return 0;
}
