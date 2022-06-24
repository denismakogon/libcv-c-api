//
//  etc.cpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//

#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

/*-----------------------------------------------------------------------*/
/*-----------------------------------etc---------------------------------*/
/*-----------------------------------------------------------------------*/

bool checkElementByIndexAt(vector<string>& vt, int index) {
    bool isPresent;
    try {
        vt.at(index);
        isPresent = true;
    } catch (out_of_range& ex) {
        isPresent = false;
    }
    return isPresent;
}

const char* stringToChar(string str) {
    const char* charPtrClassName = new char[str.length()];
    charPtrClassName = str.data();
    return charPtrClassName;
}
