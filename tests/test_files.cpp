//
//  test_files.cpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 01.07.2022.
//

#include <string>
#include <vector>

#include "include/files.hpp"
#include "include/c_api.h"

#include "opencv2/core/mat.hpp"

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
        puts("Test [readImageFile] failed!");
        exit(1);
    }
    
    retCode  = readImageFile(img, "/tmp/non-existing.img", IMREAD_COLOR);
    if (retCode != -1) {
        puts("Test [readImageFile] should have failed!");
        exit(1);
    }
    
    puts("tests [readImageFile] passed");
}
