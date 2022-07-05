#!/usr/bin/env bash

set -xe

platform="linux"
arch=$(uname -m)
lib_extension="so"
if [[ $OSTYPE == 'darwin'* ]]; then
  lib_extension="dylib"
  platform="macos"
fi
version=${1:-"$(date +'%Y.%m.%d')"}
build_dir=${2:-"build"}
version_no_dots=$(echo -e "${version}" | tr -d '.')
libname=${3:-"libcv-c-api.${version_no_dots}.${platform}.${arch}.${lib_extension}"}

rm -fr "${build_dir}"
mkdir -p "${build_dir}/include"
mkdir -p "${build_dir}/lib"

./scripts/patch-version.sh "${version}"

# shellcheck disable=SC2046
time g++ -pipe -I src/ $(pkg-config --cflags --libs opencv4) \
    -std=c++11  -dynamiclib src/*.cpp \
    -ferror-limit=1 -pthread \
    -o "${build_dir}/lib/${libname}" \
    -current_version "${version}" -compatibility_version "${version}"

cp "src/include/c_api.h" "${build_dir}/include/c_api.h"
cp "src/include/data_types.h" "${build_dir}/include/data_types.h"
cp "src/include/version.h" "${build_dir}/include/version.h"
