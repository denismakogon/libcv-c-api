#!/usr/bin/env bash

version=${1:-"latest"}

platform="linux"
arch=$(uname -m)
lib_extension="so"
if [[ $OSTYPE == 'darwin'* ]]; then
  lib_extension="dylib"
  platform="macos"
fi

libname="libcv_c_api.${platform}.${arch}.${lib_extension}"
archive_url="https://github.com/denismakogon/libcv-c-api/releases/${version}/download/${libname}.tar.gz"
lib_url="https://github.com/denismakogon/libcv-c-api/releases/${version}/download/${libname}"
