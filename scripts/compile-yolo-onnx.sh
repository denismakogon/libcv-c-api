#!/usr/bin/env bash

set -xe

model_size=${1:-"yolov5x"}

base_dir=${2:-"/tmp/YOLOv5"}

rm -fr "${base_dir}"
mkdir -p "${base_dir}"
git clone https://github.com/ultralytics/yolov5.git "${base_dir}"

python3 -mvenv "${base_dir}/.venv"
curl -vL "https://github.com/ultralytics/yolov5/releases/download/v6.1/${model_size}.pt" -o "${base_dir}/models/${model_size}.pt"

${base_dir}/.venv/bin/pip install -r ${base_dir}/requirements.txt
${base_dir}/.venv/bin/pip install onnx onnx-simplifier

${base_dir}/.venv/bin/python "${base_dir}/export.py" --weights "${base_dir}/models/${model_size}.pt" --include onnx

${base_dir}/.venv/bin/onnxsim "${base_dir}/models/${model_size}.onnx" "${base_dir}/models/simplified.onnx"
