#!/usr/bin/env bash

set -xe

test_suite_cpp_file=${1}
libname=${2}

mkdir -p build/tests
# shellcheck disable=SC2046
g++ -std=c++11 \
  $(pkg-config --cflags --libs opencv4) \
  -I src/ -Lbuild/lib build/lib/"${libname}" \
  -Wall -Werror -ferror-limit=1 \
  "${test_suite_cpp_file}" -o "build/${test_suite_cpp_file}.binary"
