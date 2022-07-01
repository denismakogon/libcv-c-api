#!/usr/bin/env bash

set -xe

version=${1:-"$(date +'%Y.%m.%d')"}
build_dir=${2:-"build"}
lib_extension="so"
if [[ $OSTYPE == 'darwin'* ]]; then
  lib_extension="dylib"
fi

libname="libopencv_c_api-${version}.${lib_extension}"

rm -fr "${build_dir:?}/*"
mkdir -p "${build_dir}/include"
mkdir -p "${build_dir}/lib"

# shellcheck disable=SC2046
g++ -I src/ $(pkg-config --cflags --libs opencv4) \
    -std=c++11  -dynamiclib src/*.cpp \
    -o "${build_dir}/lib/${libname}" \
    -current_version "${version}" -compatibility_version "${version}"

cp "src/include/c_api.h" "${build_dir}/include/c_api.h"
cp "src/include/data_types.h" "${build_dir}/include/data_types.h"
