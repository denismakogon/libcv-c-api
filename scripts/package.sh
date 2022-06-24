#!/usr/bin/env bash

set -xe

rm -fr build/*

version=${1:-"0.1"}

mkdir -p build/include
mkdir -p build/lib
pushd src && \
  g++ -I. `pkg-config --cflags --libs opencv4` \
      -std=c++11  -dynamiclib *.cpp \
      -o "../build/lib/libopencv_c_api-${version}.dylib" \
      -current_version "${version}" -compatibility_version "${version}" && \
      cp include/c_api.h ../build/include/c_api.h; \
      cp include/data_types.h ../build/include/data_types.h; \
popd;

pushd build && tar -zcvf "/tmp/libopencv_c_api.dylib-${version}.tar.gz" include lib; popd
mv "/tmp/libopencv_c_api.dylib-${version}.tar.gz" "build/libopencv_c_api.dylib-${version}.tar.gz"
rm -fr build/include build/lib
