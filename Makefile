CC = g++ -g
OPENCV_FLAGS = $(shell pkg-config --cflags --libs opencv4)
BUILD_DIR := build
UNAME_S := $(shell uname -s)
ARCH := $(shell uname -m)
LIB_EXTENSION := so
PLATFORM := linux
VERSION := $(shell date +'%Y.%m.%d')
VERSION_NO_DOTS := $(shell date +'%Y.%m.%d' | tr -d '.')
ifeq ($(UNAME_S),Darwin)
	PLATFORM = macos
	LIB_EXTENSION = dylib
endif
LIBNAME := libcv-c-api.$(VERSION_NO_DOTS).$(PLATFORM).$(ARCH).$(LIB_EXTENSION)
LIB_FILE := $(BUILD_DIR)/lib/$(LIBNAME)

all: lib test-files test-files test-image test-video test-dnn-on-images test-drawing

lib:
	$(shell rm -fr $(BUILD_DIR))
	$(shell mkdir -p $(BUILD_DIR)/include)
	$(shell mkdir -p $(BUILD_DIR)/lib)
	$(shell scripts/patch-version.sh $(VERSION))
	$(shell cp "src/include/c_api.h" $(BUILD_DIR)/include/c_api.h)
	$(shell cp "src/include/data_types.h" $(BUILD_DIR)/include/data_types.h)
	$(shell cp "src/include/version.h" $(BUILD_DIR)/include/version.h)

	$(CC) -I src/ $(OPENCV_FLAGS) -std=c++11  -dynamiclib src/*.cpp -ferror-limit=1 -pthread -o $(LIB_FILE) -current_version $(VERSION) -compatibility_version $(VERSION)

test-files:
	$(shell scripts/compile-test.sh tests/test_files.cpp $(LIBNAME))
	./build/tests/test_files.cpp.binary tests/data/cars-on-a-highway.jpeg

test-etc:
	$(shell scripts/compile-test.sh tests/test_etc.cpp $(LIBNAME))
	./build/tests/test_etc.cpp.binary

test-image:
	$(shell scripts/compile-test.sh tests/test_image.cpp $(LIBNAME))
	./build/tests/test_image.cpp.binary tests/data/cars-on-a-highway.jpeg

test-video:
	$(shell scripts/compile-test.sh tests/test_video.cpp $(LIBNAME))
	./build/tests/test_video.cpp.binary tests/data/cars-passing-by.mp4 tests/data/cars-on-a-highway.jpeg

test-dnn-on-images:
	$(shell scripts/compile-test.sh tests/test_dnn_on_images.cpp $(LIBNAME))
	./build/tests/test_dnn_on_images.cpp.binary /tmp/YOLOv5/models/simplified.onnx tests/data/coco.names tests/data/cars-on-a-highway.jpeg

test-drawing:
	$(shell scripts/compile-test.sh tests/test_drawing.cpp $(LIBNAME))
	./build/tests/test_drawing.cpp.binary /tmp/YOLOv5/models/simplified.onnx tests/data/coco.names tests/data/cars-on-a-highway.jpeg

test: lib test-files test-files test-image test-video test-dnn-on-images test-drawing


clean:
	rm -fr $(BUILD_DIR)
