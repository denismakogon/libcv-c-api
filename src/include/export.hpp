//
//  export.hpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//

#ifndef export_hpp
#define export_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"

#include "include/data_types.h"

using namespace std;
using namespace cv;

void exportVectorOf(vector<Rect>& detections, ExportableRectangle* result);
void exportVectorOf(vector<ExportableRectangles>& rectsPerFrame, ExportableRectanglesPerFrame& result);
void exportVectorOf(vector<Rect>& intermediate, PositionalFrameObjectDetectionDescriptor& pds);

#endif /* export_hpp */
