//
//  test_image.cpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 01.07.2022.
//

#include <stdio.h>

#include "include/image.hpp"
#include "include/files.hpp"
#include "include/to_string.hpp"
#include "include/c_api.h"

using namespace cv;
using namespace std;


int main(int argc, char* argv[]) {
    if (argc < 2) {
        puts("image path parameter is missing");
        puts("program [image-path]");
        exit(1);
    }

    Mat img;
    auto imagePath = string(argv[1]);
    int retCode = readImageFile(img, imagePath, IMREAD_COLOR);
    
    if (retCode != 0) {
        puts("unable to read file!");
        exit(1);
    }
    
    ExportableMat exMat;
    matToByteArray(img, exMat);
    puts(toString(exMat).c_str());
    
    Mat newImg;
    byteArrayToMat(exMat, newImg);
    puts(format("width: %d, height: %d, channels: %d, flags: %d, dims: %d",
                img.cols, img.rows, img.channels(),
                img.flags, img.dims).c_str());

    assert(!newImg.empty());
    assert(newImg.rows == img.rows);
    assert(newImg.cols == img.cols);
    assert(newImg.size == img.size);
    assert(newImg.dims == img.dims);
    assert(newImg.step == img.step);
    assert(newImg.flags == img.flags);
    assert(newImg.channels() == img.channels());
    
    puts("tests [matToByteArray | byteArrayToMat] passed");
}
