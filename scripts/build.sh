#!/usr/bin/env bash

set -xe

version=${1:-"0.1"}
build_dir=${2:-"build"}

location="../${build_dir}"

pushd src && \
  rm -fr "${location:?}/*"; \
  mkdir -p "${location}/include"; \
  mkdir -p "${location}/lib"; \

  g++ -I. `pkg-config --cflags --libs opencv4` \
      -std=c++11  -dynamiclib *.cpp \
      -o "${location}/lib/libopencv_c_api-${version}.dylib" \
      -current_version "${version}" -compatibility_version "${version}" && \
      cp "include/c_api.h" "${location}/include/c_api.h"; \
      cp "include/data_types.h" "${location}/include/data_types.h"; \
popd;
