//
//  video.hpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//

#ifndef video_hpp
#define video_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "opencv2/core/mat.hpp"

using namespace std;
using namespace cv;


int readAllFrames(string videoFilePath, vector<Mat>& frames);

#endif /* video_hpp */
