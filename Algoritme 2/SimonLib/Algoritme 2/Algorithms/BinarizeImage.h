#ifndef BINARIZEIMAGE_H
#define BINARIZEIMAGE_H

#include <ImageLib.h>

using namespace ImageLib;

//! BinarizeImage class
//
//! This class is able to convert an image to black and white by thresholding an image to a given threshold.
//!
//! Team: Localization
//! Author(s): Mitchell Werensteijn & Yusuf Syakur
//! Version: 1.0
class BinarizeImage {
public:
	//! Binarize an image.
	//
	//! This function will filter an image by a given threshold. First
	//! the image will be grayscaled. Then for every pixel value that is 
	//! bigger than the value in threshold will be white, the rest will 
	//! be black.
	//! 
	//! /param image is the image that will be thresholded.
	//! /param threshold is the threshold value, default = 127. 
	void binarizeImage(ImageRGB & image, int threshold = 127);
};

#endif

