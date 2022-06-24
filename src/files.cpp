//
//  files.cpp
//  c_api
//
//  Created by Denis Makogon on 24.06.2022.
//

#include <stdio.h>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>

#include "opencv2/core/mat.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core/utility.hpp"

#include "includes/debug.hpp"

using namespace std;
using namespace cv;
using namespace cv::samples;

/*-----------------------------------------------------------------------*/
/*-------------------------------file API--------------------------------*/
/*-----------------------------------------------------------------------*/

int readImageFile(Mat& image, string imagePath, int option) {
    debug("in readImageFile");
    int retCode = 0;
    try {
        image = imread(findFile(imagePath, true, true), option);
        if( image.empty() ) {
            retCode = -1;
        }
    } catch (Exception& ex) {
        debug(ex.what());
        retCode = -1;
    }
    debug(format("done with readImageFile, retCode: %d", retCode));
    return retCode;
}

int iterateFile(string filePath, function<void(const string&, int)> callback) {
    debug("in iterateFile");
    try {
        findFile(filePath);
    } catch (Exception& ex) {
        debug(ex.what());
        return -1;
    }
    
    ifstream inputFile(filePath.c_str());
    
    string tmp;
    int indexOf = 0;
    while (std::getline(inputFile, tmp)) {
        if (tmp.size() > 0) {
            callback(tmp, indexOf);
            indexOf++;
        }
    }
    
    inputFile.close();
    debug("done with iterateFile");
    return 0;
}

int readFileToVectorOf(string filePath, vector<string>& lines) {
    debug("in readFileToVectorOf");
    
    int retCode = iterateFile(filePath, [&](const string & line, int indexOf) {
        lines.push_back(line);
    });
    
    debug(format("done with readFileToVectorOf, retCode: %d", retCode));
    return retCode;
}
