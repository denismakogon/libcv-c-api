//
//  c_api.h
//  c_api
//
//  Created by Denis Makogon on 17.06.2022.
//

#ifndef c_api_h
#define c_api_h

#include "include/data_types.h"

#include <stdbool.h>

// C API
#ifdef __cplusplus
extern "C" {
#endif

// a copy of imgcodecs.h
// start
enum ImreadModes {
       IMREAD_UNCHANGED            = -1, //!< If set, return the loaded image as is (with alpha channel, otherwise it gets cropped). Ignore EXIF orientation.
       IMREAD_GRAYSCALE            = 0,  //!< If set, always convert image to the single channel grayscale image (codec internal conversion).
       IMREAD_COLOR                = 1,  //!< If set, always convert image to the 3 channel BGR color image.
       IMREAD_ANYDEPTH             = 2,  //!< If set, return 16-bit/32-bit image when the input has the corresponding depth, otherwise convert it to 8-bit.
       IMREAD_ANYCOLOR             = 4,  //!< If set, the image is read in any possible color format.
       IMREAD_LOAD_GDAL            = 8,  //!< If set, use the gdal driver for loading the image.
       IMREAD_REDUCED_GRAYSCALE_2  = 16, //!< If set, always convert image to the single channel grayscale image and the image size reduced 1/2.
       IMREAD_REDUCED_COLOR_2      = 17, //!< If set, always convert image to the 3 channel BGR color image and the image size reduced 1/2.
       IMREAD_REDUCED_GRAYSCALE_4  = 32, //!< If set, always convert image to the single channel grayscale image and the image size reduced 1/4.
       IMREAD_REDUCED_COLOR_4      = 33, //!< If set, always convert image to the 3 channel BGR color image and the image size reduced 1/4.
       IMREAD_REDUCED_GRAYSCALE_8  = 64, //!< If set, always convert image to the single channel grayscale image and the image size reduced 1/8.
       IMREAD_REDUCED_COLOR_8      = 65, //!< If set, always convert image to the 3 channel BGR color image and the image size reduced 1/8.
       IMREAD_IGNORE_ORIENTATION   = 128 //!< If set, do not rotate the image according to EXIF's orientation flag.
     };

//! Imwrite flags
enum ImwriteFlags {
       IMWRITE_JPEG_QUALITY        = 1,  //!< For JPEG, it can be a quality from 0 to 100 (the higher is the better). Default value is 95.
       IMWRITE_JPEG_PROGRESSIVE    = 2,  //!< Enable JPEG features, 0 or 1, default is False.
       IMWRITE_JPEG_OPTIMIZE       = 3,  //!< Enable JPEG features, 0 or 1, default is False.
       IMWRITE_JPEG_RST_INTERVAL   = 4,  //!< JPEG restart interval, 0 - 65535, default is 0 - no restart.
       IMWRITE_JPEG_LUMA_QUALITY   = 5,  //!< Separate luma quality level, 0 - 100, default is 0 - don't use.
       IMWRITE_JPEG_CHROMA_QUALITY = 6,  //!< Separate chroma quality level, 0 - 100, default is 0 - don't use.
       IMWRITE_PNG_COMPRESSION     = 16, //!< For PNG, it can be the compression level from 0 to 9. A higher value means a smaller size and longer compression time. If specified, strategy is changed to IMWRITE_PNG_STRATEGY_DEFAULT (Z_DEFAULT_STRATEGY). Default value is 1 (best speed setting).
       IMWRITE_PNG_STRATEGY        = 17, //!< One of cv::ImwritePNGFlags, default is IMWRITE_PNG_STRATEGY_RLE.
       IMWRITE_PNG_BILEVEL         = 18, //!< Binary level PNG, 0 or 1, default is 0.
       IMWRITE_PXM_BINARY          = 32, //!< For PPM, PGM, or PBM, it can be a binary format flag, 0 or 1. Default value is 1.
       IMWRITE_EXR_TYPE            = (3 << 4) + 0, /* 48 */ //!< override EXR storage type (FLOAT (FP32) is default)
       IMWRITE_EXR_COMPRESSION     = (3 << 4) + 1, /* 49 */ //!< override EXR compression type (ZIP_COMPRESSION = 3 is default)
       IMWRITE_WEBP_QUALITY        = 64, //!< For WEBP, it can be a quality from 1 to 100 (the higher is the better). By default (without any parameter) and for quality above 100 the lossless compression is used.
       IMWRITE_PAM_TUPLETYPE       = 128,//!< For PAM, sets the TUPLETYPE field to the corresponding string value that is defined for the format
       IMWRITE_TIFF_RESUNIT = 256,//!< For TIFF, use to specify which DPI resolution unit to set; see libtiff documentation for valid values
       IMWRITE_TIFF_XDPI = 257,//!< For TIFF, use to specify the X direction DPI
       IMWRITE_TIFF_YDPI = 258, //!< For TIFF, use to specify the Y direction DPI
       IMWRITE_TIFF_COMPRESSION = 259, //!< For TIFF, use to specify the image compression scheme. See libtiff for integer constants corresponding to compression formats. Note, for images whose depth is CV_32F, only libtiff's SGILOG compression scheme is used. For other supported depths, the compression scheme can be specified by this flag; LZW compression is the default.
       IMWRITE_JPEG2000_COMPRESSION_X1000 = 272 //!< For JPEG2000, use to specify the target compression rate (multiplied by 1000). The value can be from 0 to 1000. Default is 1000.
     };
// end

const char* ExportableRectangle_toString(struct ExportableRectangle *ExportableRectangle);

const char* ObjectDetectionDescriptor_toString(struct ObjectDetectionDescriptor *ObjectDetectionDescriptor);

const char * PositionalFrameObjectDetectionDescriptor_toString(struct PositionalFrameObjectDetectionDescriptor* PositionalFrameObjectDetectionDescriptor);

int imageToMatrix(const char* imagePath, int option, struct ExportableMat *ExportableMat);

int runClassificationsOnImage(const char* classifierPath, const char* imagePath,
                              struct PositionalFrameObjectDetectionDescriptor *PositionalFrameObjectDetectionDescriptor);

int processVideoFile(const char* classifierPath, const char* videoFilePath,
                     struct ExportableRectanglesPerFrame* ExportableRectanglesPerFrame);

int runDetectionsOnVideo(const char* videoFilePath, const char* modelPath,
                         const char* modelWeights, const char* cocoaClassesFilePath,
                         double confidenceThresholdMin,
                         double confidenceThresholdMax);

int runDetectionsOnImage(const char* imagePath, const char* modelPath,
                         const char* modelWeights, const char* cocoaClassesFilePath,
                         struct PositionalFrameObjectDetectionDescriptor* PositionalFrameObjectDetectionDescriptor,
                         double confidenceThresholdMin,
                         double confidenceThresholdMax);

int drawDetectionsOnImage(const char* sourceImagePath, const char* finalImagePath,
                          struct PositionalFrameObjectDetectionDescriptor *PositionalFrameObjectDetectionDescriptor,
                          double scale);

#ifdef __cplusplus
}
#endif

#endif /* c_api_h */
