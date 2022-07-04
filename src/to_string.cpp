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
    debug("in toString(PositionalFrameObjectDetectionDescriptor&)");
    string res = "";
    for (int i = 0; i < object.size; i++) {
        debug(format("%d ", i) + toString(object.detections[i]));
        res += toString(object.detections[i]);
    }
    debug("done with toString(PositionalFrameObjectDetectionDescriptor&)");
    return format("position: %d, detections: %s", object.position, res.c_str());
}
