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
libname="libcv-c-api.${platform}.${arch}.${lib_extension}"
archive="${libname}.tar.gz"

/bin/bash scripts/compile-lib.sh "${version}" "${build_dir}" "${libname}"

pushd build && tar -zcvf "/tmp/${archive}" include lib; popd
mv "/tmp/${archive}" "${build_dir:?}/${archive}"
# shellcheck disable=SC2115
rm -fr "${build_dir}/include" "${build_dir}/lib"
