//
//  to_string.cpp
//  c_api
//
//  Created by Denis Makogon on 24.06.2022.
//

#include <string>

#include "opencv2/core/utility.hpp"

#include "include/data_types.h"

using namespace std;
using namespace cv;

/*-----------------------------------------------------------------------*/
/*------------------------------toString API-----------------------------*/
/*-----------------------------------------------------------------------*/

string toString(ExportableRectangle& object) {
    return format("X=(%d, %d) Y=(%d,%d) width=%d heights=%d",
                  object.x0, object.y0,
                  object.x1, object.y1,
                  object.width, object.height);
}

string toString(ObjectDetectionDescriptor& object) {
    return format("confidence: %6.4lf, rectange: [%s] class: %s\n",
                  object.confidence, toString(object.rect).data(), object.className);
}

string toString(PositionalFrameObjectDetectionDescriptor& object) {
    string res = "";
    for (int i = 0; i < object.size; i++) {
        res += toString(object.detections[i]);
    }
    return format("position: %d, detections: %s", object.position, res.c_str());
}
