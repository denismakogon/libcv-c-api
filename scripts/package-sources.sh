#!/usr/bin/env bash

set -xe

build_dir=${1:-"build"}
archive_name="libcv_c_api.src.tar.gz"

mkdir -p "${build_dir}"

tar -zcvf "/tmp/${archive_name}" scripts/ src/
mv "/tmp/${archive_name}" "${build_dir:?}/${archive_name}"
