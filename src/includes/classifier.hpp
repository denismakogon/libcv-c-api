//
//  classifier.hpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//

#ifndef classifier_hpp
#define classifier_hpp

#include <stdio.h>
#include <string>

#include "includes/data_types.h"

using namespace std;

int runClassificationsOnImage(string classifierPath, string imagePath, PositionalFrameObjectDetectionDescriptor& pds);

int runClassificationsOnVideo(string classifierPath, string videoFilePath,
                              ExportableRectanglesPerFrame& exportableResult);

#endif /* classifier_hpp */
