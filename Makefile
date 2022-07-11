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
LIB=libcv-c-api
LIB_DEF = $(LIB).$(VERSION_NO_DOTS)
LIBNAME = $(LIB_DEF).$(PLATFORM).$(ARCH).$(LIB_EXTENSION)
LIB_FILE = $(BUILD_DIR)/lib/$(LIBNAME)
LIB_BINARY_ARCHIVE_NAME = $(LIBNAME).tar.gz
LIB_SOURCES_ARCHIVE_NAME = libcv-c-api.src.tar.gz
JAVA_SOURCES_DIR = $(BUILD_DIR)/src/main/java

MAVEN_FLAGS = -Dversion=$(VERSION) -Dos=$(PLATFORM) -Darch=$(ARCH) -Dclassifiers=$(PLATFORM) -Dversion_no_dots=$(VERSION_NO_DOTS) -Dlib=$(LIB)

all: clean lib test

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
	$(MAKE) test-suite suite=tests/test_etc.cpp
	$(MAKE) test-suite suite=tests/test_files.cpp args="tests/data/cars-on-a-highway.jpeg"
	$(MAKE) test-suite suite=tests/test_image.cpp args="tests/data/cars-on-a-highway.jpeg"
	$(MAKE) test-suite suite=tests/test_video.cpp args="tests/data/cars-passing-by.mp4 tests/data/cars-on-a-highway.jpeg"
	$(MAKE) test-suite suite=tests/test_dnn_on_images.cpp args="/tmp/YOLOv5/models/simplified.onnx tests/data/coco.names tests/data/cars-on-a-highway.jpeg"
	$(MAKE) test-suite suite=tests/test_drawing.cpp args="/tmp/YOLOv5/models/simplified.onnx tests/data/coco.names tests/data/cars-on-a-highway.jpeg"

java-src:
	jextract --source -t clang.libcv -I src --header-class-name clang --output $(JAVA_SOURCES_DIR) $(args) src/include/c_api.h

jar: java-src
	mvn clean package $(MAVEN_FLAGS)

archive-sources:
	$(shell tar -zcvf $(BUILD_DIR)/$(LIB_SOURCES_ARCHIVE_NAME) src/ Makefile)

archive-lib: lib
	$(shell tar -zcvf $(BUILD_DIR)/$(LIB_BINARY_ARCHIVE_NAME) $(BUILD_DIR)/include $(BUILD_DIR)/lib)

archive: jar archive-sources archive-lib

deploy-jar: jar
	mvn deploy:deploy-file \
		  -DgroupId=clang \
		  -DartifactId=libcv \
		  -Dpackaging=jar \
		  -Dfile=target/$(LIB).$(VERSION).jar \
		  -DrepositoryId=github \
		  -Durl=https://maven.pkg.github.com/denismakogon/libcv-c-api \
		  $(MAVEN_FLAGS)
