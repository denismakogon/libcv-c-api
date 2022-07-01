#!/usr/bin/env bash

set -xe

version=${1:-"$(date +'%Y.%m.%d')"}
build_dir=${2:-"build"}

location="${build_dir}"

rm -fr "${location:?}/*"
mkdir -p "${location}/include"
mkdir -p "${location}/lib"

# shellcheck disable=SC2046
g++ -I src/ $(pkg-config --cflags --libs opencv4) \
    -std=c++11  -dynamiclib src/*.cpp \
    -o "${location}/lib/libopencv_c_api-${version}.dylib" \
    -current_version "${version}" -compatibility_version "${version}"

cp "src/include/c_api.h" "${location}/include/c_api.h"
cp "src/include/data_types.h" "${location}/include/data_types.h"
