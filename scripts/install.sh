#!/bin/sh

#  install.sh
#  cpp-to-c-api
#
#  Created by Denis Makogon on 06.07.2022.
#  

set -xe

version=${1:-"latest"}
install_dir="/usr/local"


base_url="https://github.com/denismakogon/libcv-c-api/releases/${version}/download"
lib_name="libcv-c-api"
archive="${lib_name}.src.tar.gz"
lib_archive_url="${base_url}/${archive}"

include_folder=${install_dir}/include/${lib_name}
lib_folder=${install_dir}/lib/${lib_name}

rm -fr "/tmp/${lib_name}"
rm -fr ${include_folder}
rm -fr ${lib_folder}

mkdir -p "/tmp/${lib_name}"
mkdir -p ${include_folder}
mkdir -p ${lib_folder}

curl -L "${lib_archive_url}" | tar xvf - -C "/tmp/${lib_name}"
pushd "/tmp/${lib_name}" && make lib; popd

build_folder="/tmp/${lib_name}/build"
lib_file=$(ls ${build_folder}/lib)

cp -r ${build_folder}/include ${include_folder}
cp -r ${build_folder}/lib/${lib_file} ${lib_folder}
