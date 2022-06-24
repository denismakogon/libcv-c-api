//
//  drawing.cpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//

#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

#include "includes/debug.hpp"
#include "includes/files.hpp"

#include "includes/data_types.h"

using namespace std;
using namespace cv;

/*-----------------------------------------------------------------------*/
/*-----------------------------Drawing API-------------------------------*/
/*-----------------------------------------------------------------------*/

const static Scalar colors[] = {
    Scalar(255,0,0),
    Scalar(255,128,0),
    Scalar(255,255,0),
    Scalar(0,255,0),
    Scalar(0,128,255),
    Scalar(0,255,255),
    Scalar(0,0,255),
    Scalar(255,0,255)
};

int drawDetectionsOnImage(string sourceImagePath, string finalImagePath,
                          PositionalFrameObjectDetectionDescriptor& pds,
                          double scale = 1.2) {
    debug("in drawDetectionsOnImage");
    Mat source, result;
    int retCode = readImageFile(source, sourceImagePath, IMREAD_COLOR);
    if ( retCode != 0 ) {
        return retCode;
    }
    
    source.copyTo(result);
    
    for (long i = 0; i < pds.size; i++) {
        Scalar color = colors[i%8];
        ObjectDetectionDescriptor d = pds.detections[i];
        ExportableRectangle r = d.rect;
        rectangle(result, Point(cvRound(r.x0 * scale), cvRound(r.y0 * scale)),
                  Point(cvRound((r.x0 + r.width-1) * scale),
                        cvRound((r.y0 + r.height-1) * scale)),
                  color, 3, 8, 0);
    }
    
    debug(format("done with drawDetectionsOnImage, retCode: %d", retCode));
    return static_cast<int>(imwrite(finalImagePath, result));
}

