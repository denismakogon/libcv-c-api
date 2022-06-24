//
//  debug.cpp
//  c_api
//
//  Created by Denis Makogon on 23.06.2022.
//
#include <iostream>
#include <cstdio>

using namespace std;

/*-----------------------------------------------------------------------*/
/*---------------------------------DEBUG---------------------------------*/
/*-----------------------------------------------------------------------*/

void debug(string message) {
    string flag = getenv("DEBUG") ? getenv("DEBUG") : string("0");
    bool debugEnabled = string("1").compare(flag) == 0;
    if (debugEnabled) {
        puts(message.c_str());
    }
}
