#!/usr/bin/env bash

set -xe

model_size=${1:-"yolov5x"}

rm -fr /tmp/YOLOv5
mkdir -p /tmp/YOLOv5
git clone https://github.com/ultralytics/yolov5.git /tmp/YOLOv5

python3 -mvenv /tmp/YOLOv5/.venv && source /tmp/YOLOv5/.venv/bin/activate
pip install -r /tmp/YOLOv5/requirements.txt
pip install onnx

curl -vL "https://github.com/ultralytics/yolov5/releases/download/v6.1/${model_size}.pt" -o "/tmp/YOLOv5/models/${model_size}.pt"
python /tmp/YOLOv5/export.py --weights /tmp/YOLOv5/models/yolov5x.pt --include onnx

pip3 install onnx-simplifier
onnxsim "/tmp/YOLOv5/models/${model_size}.onnx" "/tmp/YOLOv5/models/${model_size}.simplified.onnx"

deactivate
