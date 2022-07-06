//
//  image.cpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//

#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

#include "include/data_types.h"
#include "include/debug.hpp"
#include "include/etc.hpp"
#include "include/files.hpp"


using namespace std;
using namespace cv;
using namespace cv::samples;

/*-----------------------------------------------------------------------*/
/*------------------------------Matrix API-------------------------------*/
/*-----------------------------------------------------------------------*/

void matToByteArray(Mat& image, ExportableMat& exMat) {
    unsigned long size = image.total() * image.elemSize();
    char * bytes = new char[size];
    memcpy(bytes,image.data,size * sizeof(char));
    exMat = (ExportableMat) {
        .data = bytes,
        .width = image.cols,
        .height = image.rows,
        .channels = image.channels(),
        .dimentions = image.dims,
        .flags = image.flags,
    };
}

void byteArrayToMat(ExportableMat& exMat, Mat& mat) {
    int* sizes = new int[2] {exMat.height, exMat.width};
    mat = Mat(exMat.dimentions, sizes, CV_8UC(exMat.channels), exMat.data).clone();
}

int imageToMatrix(string imagePath, int option, ExportableMat& exMat) {
    debug("in imageToMatrix");
    Mat img;
    
    int retCode = 0;
    retCode = readImageFile(img, imagePath, option);
    if (retCode != 0) {
        return retCode;
    }
    
    matToByteArray(img, exMat);
    debug(format("done with imageToMatrix, retCode: %d", retCode));
    return retCode;
}
