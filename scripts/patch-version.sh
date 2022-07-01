#!/usr/bin/env bash

set -xe

version=${1:-"$(date +'%Y.%m.%d')"}

if [[ $IN_CI == 'yes'* ]]; then
  major_version=$(echo "${version}" | tr '.' ' ' | awk '{print $1}')
  minor_version=$(echo "${version}" | tr '.' ' ' | awk '{print $2}')
  micro_version=$(echo "${version}" | tr '.' ' ' | awk '{print $NF}')

  sed "s/latest/$version/g;s/major/$major_version/g;s/minor/$minor_version/g;s/micro/$micro_version/g" src/include/version.h.t > src/include/version.h
fi
