//
//  data_types.h
//  c_api
//
//  Created by Denis Makogon on 17.06.2022.
//

#ifndef data_types_h
#define data_types_h

struct ExportableMat {
    char* data;
    int width;
    int height;
    int channels;
    int flags;
    int dimentions;
};

struct ExportableRectangle {
    int x0, y0;
    int x1, y1;
    int width, height;
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

struct FrameDetections {
    unsigned long size;
    struct PositionalFrameObjectDetectionDescriptor* frameDetections;
};

#endif /* data_types_h */
