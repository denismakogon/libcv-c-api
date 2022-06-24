//
//  image.hpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//

#ifndef image_hpp
#define image_hpp

#include <stdio.h>
#include <string>

#include "opencv2/core/mat.hpp"

#include "includes/data_types.h"

using namespace std;
using namespace cv;

void matToByteArray(Mat& image, ExportableMat& exMat);
void byteArrayToMat(ExportableMat& exMat, Mat& mat);
int imageToMatrix(string imagePath, int option, ExportableMat& exMat);

#endif /* image_hpp */
