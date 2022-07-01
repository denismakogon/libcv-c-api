#!/usr/bin/env bash

set -xe

version=${1:-"$(date +'%Y.%m.%d')"}
build_dir=${2:-"build"}

/bin/bash scripts/compile-lib.sh "${version}" "${build_dir}"

pushd build && tar -zcvf "/tmp/libopencv_c_api.dylib-${version}.tar.gz" include lib; popd
mv "/tmp/libopencv_c_api.dylib-${version}.tar.gz" "${build_dir:?}/libopencv_c_api.dylib-${version}.tar.gz"
