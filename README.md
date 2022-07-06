#  C++ to C API to Java API

The purpose of this project to showcase the abilities to degrade C++ API to C API to make them consumable in Java using Project Panama Foreign Function & Memory API.

## Tools

- [OpenCV 4.5+](https://github.com/opencv/opencv)
- [DLib](https://github.com/davisking/dlib)

### Prerequisites

```shell
brew install opencv
brew install dlib
brew install pkg-config
```

Make sure that `pkg-config` points to the latest OpenCV version:
```shell
$ pkg-config --modversion opencv4

4.5.5
```

If not, please copy OpenCV config file to `pkg-config` source folder:
```shell
cp /usr/local/Cellar/opencv/4.5.5_2/lib/pkgconfig/opencv4.pc /usr/local/lib/pkgconfig/opencv4.pc 
```

### Compiling a library

Check that `pkg-config` provides necessary paths to include folders and libraries:
```shell
$ pkg-config --cflags --libs opencv4

-I/usr/local/opt/opencv/include/opencv4 -L/usr/local/opt/opencv/lib -lopencv_gapi -lopencv_stitching -lopencv_alphamat -lopencv_aruco -lopencv_barcode -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform -lopencv_line_descriptor -lopencv_mcc -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_highgui -lopencv_datasets -lopencv_text -lopencv_plot -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_wechat_qrcode -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_dnn -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core

```

Compile a library
```shell
make lib -j$(nproc)
```

a library and headers will be stored at:
```shell
build/lib/libopencv_c_api.dylib
```

### Running test

All tests:
```shell
make test
```

Specific test:
```shell
make test-suite tests/<test-suite>.cpp args="<test-arguments>"
```
