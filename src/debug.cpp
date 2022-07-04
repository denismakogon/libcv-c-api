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

bool debugEnabled() {
    string flag = getenv("DEBUG") ? getenv("DEBUG") : string("0");
    return string("1").compare(flag) == 0;
}

void debug(string message) {
    if (debugEnabled()) {
        puts(message.c_str());
    }
}
