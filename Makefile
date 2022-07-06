CC = g++

CFLAGS = -std=c++11 -Wall -Werror -ferror-limit=1 -I src/
CFLAGS += $(shell pkg-config --cflags --libs opencv4)

BUILD_DIR = build
UNAME_S = $(shell uname -s)
ARCH = $(shell uname -m)
LIB_EXTENSION = so
PLATFORM = linux
VERSION = $(shell date +'%Y.%m.%d')
VERSION_NO_DOTS = $(shell date +'%Y.%m.%d' | tr -d '.')
ifeq ($(UNAME_S),Darwin)
	PLATFORM = macos
	LIB_EXTENSION = dylib
endif
LIBNAME = libcv-c-api.$(VERSION_NO_DOTS).$(PLATFORM).$(ARCH).$(LIB_EXTENSION)
LIB_FILE = $(BUILD_DIR)/lib/$(LIBNAME)
LIB_BINARY_ARCHIVE_NAME = $(LIBNAME).tar.gz
LIB_SOURCES_ARCHIVE_NAME = libcv-c-api.src.tar.gz

all: clean lib test-files test-files test-image test-video test-dnn-on-images test-drawing

clean:
	rm -fr $(BUILD_DIR)

lib: clean
	$(shell rm -fr $(BUILD_DIR))
	$(shell mkdir -p $(BUILD_DIR)/include)
	$(shell mkdir -p $(BUILD_DIR)/lib)

	$(shell scripts/patch-version.sh $(VERSION))

	$(shell cp "src/include/c_api.h" $(BUILD_DIR)/include/c_api.h)
	$(shell cp "src/include/data_types.h" $(BUILD_DIR)/include/data_types.h)
	$(shell cp "src/include/version.h" $(BUILD_DIR)/include/version.h)

	$(CC) $(CFLAGS) -dynamiclib src/*.cpp -o $(LIB_FILE) -current_version $(VERSION) -compatibility_version $(VERSION)

.PHONY: test-suite
test-suite:
	$(shell mkdir -p build/tests)
	$(CC) $(CFLAGS) -Lbuild/lib build/lib/$(LIBNAME) $(suite) -o build/$(suite).binary
	./build/$(suite).binary $(args)

test: clean lib
	$(MAKE) test-suite suite=tests/test_files.cpp args="tests/data/cars-on-a-highway.jpeg tests/data/cars-passing-by.mp4"
	$(MAKE) test-suite suite=tests/test_etc.cpp
	$(MAKE) test-suite suite=tests/test_image.cpp args="tests/data/cars-on-a-highway.jpeg"
	$(MAKE) test-suite suite=tests/test_video.cpp args="tests/data/cars-passing-by.mp4 tests/data/cars-on-a-highway.jpeg"
	$(MAKE) test-suite suite=tests/test_dnn_on_images.cpp args="/tmp/YOLOv5/models/simplified.onnx tests/data/coco.names tests/data/cars-on-a-highway.jpeg"
	$(MAKE) test-suite suite=tests/test_drawing.cpp args="/tmp/YOLOv5/models/simplified.onnx tests/data/coco.names tests/data/cars-on-a-highway.jpeg"

archive: clean lib
	$(shell tar -zcvf $(BUILD_DIR)/$(LIB_SOURCES_ARCHIVE_NAME) src/ Makefile)
	$(shell tar -zcvf $(BUILD_DIR)/$(LIB_BINARY_ARCHIVE_NAME) $(BUILD_DIR)/include $(BUILD_DIR)/lib)
