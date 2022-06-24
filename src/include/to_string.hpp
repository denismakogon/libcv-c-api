//
//  to_string.hpp
//  c_api
//
//  Created by Denis Makogon on 24.06.2022.
//

#ifndef to_string_hpp
#define to_string_hpp

#include <stdio.h>
#include <string>

#include "opencv2/core/utility.hpp"

#include "include/data_types.h"

using namespace std;
using namespace cv;

string toString(ExportableRectangle& object);
string toString(ObjectDetectionDescriptor& object);
string toString(PositionalFrameObjectDetectionDescriptor& object);

#endif /* to_string_hpp */
