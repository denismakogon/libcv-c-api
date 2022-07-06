//
//  test_etc.cpp
//  cpp-to-c-api
//
//  Created by Denis Makogon on 03.07.2022.
//

#include <stdio.h>
#include <vector>
#include <string>

#include "include/etc.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    vector<string> someVector {string("a"), string("b"),
        string("c"), string("d"), string("e")};
    
    assert(false == checkElementByIndexAt(someVector, 10));
    assert(true == checkElementByIndexAt(someVector, 2));
    
    puts("test [checkElementByIndexAt] passed");
}
