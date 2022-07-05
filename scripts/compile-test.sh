#!/usr/bin/env bash

set -xe

test_suite_cpp_file=${1}

libname="cv-c-api"
lib_extension="so"
if [[ $OSTYPE == 'darwin'* ]]; then
  lib_extension="dylib"
fi

./scripts/compile-lib.sh "$(date +'%Y.%m.%d')" "build" "${libname}.${lib_extension}"

mkdir -p build/tests
# shellcheck disable=SC2046
time g++ -pipe -std=c++11 \
  $(pkg-config --cflags --libs opencv4) \
  -I src/ -Lbuild/lib build/lib/"${libname}.${lib_extension}" \
  -Wall -Werror -ferror-limit=1 \
  "${test_suite_cpp_file}" -o "build/${test_suite_cpp_file}.binary"
