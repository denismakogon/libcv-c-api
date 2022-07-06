//
//  print.hpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 04.07.2022.
//

#ifndef print_hpp
#define print_hpp

#include "include/data_types.h"

void print(ExportableMat& object);
void print(ExportableRectangle& object);
void print(ObjectDetectionDescriptor& object);
void print(PositionalFrameObjectDetectionDescriptor& object);
void print(FrameDetections& object);

#endif /* print_hpp */
