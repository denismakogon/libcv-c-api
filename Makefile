CC = g++ -g
OPENCV_FLAGS = $(shell pkg-config --cflags --libs opencv4)
BUILD_DIR := build
UNAME_S := $(shell uname -s)
ARCH := $(shell uname -m)
LIB_EXTENSION := so
PLATFORM := linux
VERSION := $(shell date +'%Y.%m.%d')
VERSION_NO_DOTS := $(shell date +'%Y.%m.%d' | tr -d '.')
LIBNAME := libcv-c-api.$(VERSION_NO_DOTS).$(PLATFORM).$(ARCH).$(LIB_EXTENSION)
LIB_FILE := $(BUILD_DIR)/lib/$(LIBNAME)
ifeq ($(UNAME_S),Darwin)
	PLATFORM = macos
	LIB_EXTENSION = dylib
endif

all: lib

lib:

	$(shell rm -fr $(BUILD_DIR))
	$(shell mkdir -p $(BUILD_DIR)/include)
	$(shell mkdir -p $(BUILD_DIR)/lib)

	$(shell scripts/patch-version.sh $(VERSION))

	$(shell cp "src/include/c_api.h" $(BUILD_DIR)/include/c_api.h)
	$(shell cp "src/include/data_types.h" $(BUILD_DIR)/include/data_types.h)
	$(shell cp "src/include/version.h" $(BUILD_DIR)/include/version.h)

	$(CC) -I src/ $(OPENCV_FLAGS) -std=c++11  -dynamiclib src/*.cpp -ferror-limit=1 -pthread -o $(LIB_FILE) -current_version $(VERSION) -compatibility_version $(VERSION)
 

clean:
	rm -fr build/
