//
//  data_types.h
//  c_api
//
//  Created by Denis Makogon on 17.06.2022.
//

#ifndef data_types_h
#define data_types_h

struct ExportableMat {
    char* matContent;
    int width;
    int height;
};

struct ExportableRectangle {
    int x, y, width, height;
};

struct ExportableRectangles {
    struct ExportableRectangle *array;
    unsigned long size;
};

struct ExportableRectanglesPerFrame {
    struct ExportableRectangles *array;
    unsigned long size;
};

struct ObjectDetectionDescriptor {
    char* className;
    double confidence;
    struct ExportableRectangle rect;
};

struct PositionalFrameObjectDetectionDescriptor {
    int position;
    unsigned long size;
    struct ObjectDetectionDescriptor* detections;
};

#endif /* data_types_h */
