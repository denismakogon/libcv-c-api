#!/usr/bin/env bash

set -xe

version=${1:-"$(date +'%Y.%m.%d')"}
build_dir=${2:-"build"}
platform="linux"
arch=$(uname -m)
lib_extension="so"
if [[ $OSTYPE == 'darwin'* ]]; then
  lib_extension="dylib"
  platform="macos"
fi
libname="libopencv_c_api-${version}.${platform}.${arch}.${lib_extension}"

/bin/bash scripts/compile-lib.sh "${version}" "${build_dir}"

pushd build && tar -zcvf "/tmp/${libname}" include lib; popd
mv "/tmp/${libname}" "${build_dir:?}/${libname}"
