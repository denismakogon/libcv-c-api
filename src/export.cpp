//
//  export.cpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//

#include <string>
#include <vector>

#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"

#include "include/data_types.h"

using namespace std;
using namespace cv;

/*-----------------------------------------------------------------------*/
/*---------------------------vector export API---------------------------*/
/*-----------------------------------------------------------------------*/

void exportVectorOf(vector<Rect>& detections, ExportableRectangle* result) {
    for(int i = 0; i < detections.size(); i++) {
        Rect r = detections[i];
        result[i] = (ExportableRectangle) {
            .x0 = r.x, .y0 = r.y,
            .x1 = r.x + r.width-1,
            .y1 = r.y + r.height-1,
            .width = r.width,
            .height = r.height
        };
    }
}

void exportVectorOf(vector<ExportableRectangles>& rectsPerFrame, ExportableRectanglesPerFrame& result) {
    result = (ExportableRectanglesPerFrame) {};
    result.size = rectsPerFrame.size();
    result.array = rectsPerFrame.data();
}

void exportVectorOf(vector<Rect>& intermediate, PositionalFrameObjectDetectionDescriptor& pds) {
    vector<ObjectDetectionDescriptor> ds;
    for (auto r: intermediate) {
        ds.push_back((ObjectDetectionDescriptor) {
                        .className = strdup("unknown"),
                        .confidence = 0,
                        .rect = (ExportableRectangle) {
                            .x0 = r.x, .y0 = r.y,
                            .x1 = r.x + r.width,
                            .y1 = r.y + r.height,
                            .width = r.width,
                            .height = r.height
                        }
        });
    }

    pds = (PositionalFrameObjectDetectionDescriptor) {
        .position = 0,
        .size = intermediate.size(),
        .detections = ds.data()
    };
}
