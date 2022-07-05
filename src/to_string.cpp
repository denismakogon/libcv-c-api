//
//  to_string.cpp
//  c_api
//
//  Created by Denis Makogon on 24.06.2022.
//

#include <string>

#include "opencv2/core/utility.hpp"

#include "include/data_types.h"
#include "include/debug.hpp"

using namespace std;
using namespace cv;

/*-----------------------------------------------------------------------*/
/*------------------------------toString API-----------------------------*/
/*-----------------------------------------------------------------------*/

string toString(ExportableMat& exMat) {
    return format("width: %d, height: %d, channels: %d, flags: %d, dims: %d",
                  exMat.width, exMat.height, exMat.channels,
                  exMat.flags, exMat.dimentions);
}

string toString(ExportableRectangle& object) {
    return format("X=(%d, %d) Y=(%d,%d) width=%d heights=%d",
                  object.x0, object.y0,
                  object.x1, object.y1,
                  object.width, object.height);
}

string toString(ObjectDetectionDescriptor& object) {
    return format("confidence: %6.4lf, rectange: [%s] class: %s\n",
                  object.confidence, toString(object.rect).c_str(), object.className);
}

string toString(PositionalFrameObjectDetectionDescriptor& object) {
    return format("position: %d, number of detections: %lu", object.position, object.size);
}

string toString(FrameDetections& object) {
    return format("number of frames: %lu", object.size);
}
