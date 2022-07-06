#!/bin/sh

#  install.sh
#  cpp-to-c-api
#
#  Created by Denis Makogon on 06.07.2022.
#  

set -xe

version=${1:-"latest"}
rm -fr

base_url="https://github.com/denismakogon/libcv-c-api/releases/${version}/download"
lib_name="libcv-c-api"
archive="${lib_name}.src.tar.gz"
lib_archive_url="${base_url}/${archive}"

rm -fr "/tmp/${lib_name}"
mkdir -p "/tmp/${lib_name}"

curl -L "${lib_archive_url}" | tar xvf - -C "/tmp/${lib_name}"
pushd "/tmp/${lib_name}" && make lib; popd

