//
//  drawing.hpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//

#ifndef drawing_hpp
#define drawing_hpp

#include <stdio.h>
#include <string>

#include "include/data_types.h"

using namespace std;

int drawDetectionsOnImage(string sourceImagePath, string finalImagePath,
                          PositionalFrameObjectDetectionDescriptor& pds,
                          double scale=1.2);

#endif /* drawing_hpp */
