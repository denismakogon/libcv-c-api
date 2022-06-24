//
//  files.hpp
//  c_api
//
//  Created by Denis Makogon on 24.06.2022.
//

#ifndef files_hpp
#define files_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include "opencv2/core/mat.hpp"

using namespace cv;
using namespace std;

int iterateFile(string filePath, function<void (const string&, int)> callback);
int readFileToVectorOf(string filePath, vector<string>& lines);
int readImageFile(Mat& image, string imagePath, int option);

#endif /* files_hpp */
