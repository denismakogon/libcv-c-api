//
//  print.cpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 04.07.2022.
//

#include <iostream>
#include <cstdio>

#include "include/data_types.h"

#include "include/debug.hpp"
#include "include/to_string.hpp"

using namespace std;

void print(ExportableMat& object) {
    puts(toString(object).c_str());
}

void print(ExportableRectangle& object) {
    puts(toString(object).c_str());
}

void print(ObjectDetectionDescriptor& object) {
    puts(toString(object).c_str());
}

void print(PositionalFrameObjectDetectionDescriptor& object) {
    debug("in print(PositionalFrameObjectDetectionDescriptor)");
    puts(format("position: %d, detections number: %lu, detections:",
                object.position, object.size).c_str());
    for (auto i = 0; i < object.size; i++) {
        printf("idx=%d ", i);
        print(object.detections[i]);
    }

    debug("done with print(PositionalFrameObjectDetectionDescriptor)");
}
