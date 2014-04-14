#ifndef HIGHPASSFILTER_H 
#define HIGHPASSFILTER_H

#include <ImageLib.h>

using namespace ImageLib;

//! HighPassFilter class
//
//! This class is able to high pass filter an image.
//!
//! Team: Localization
//! Author(s): Mitchell Werensteijn & Yusuf Syakur
//! Version: 1.0
class HighPassFilter {
public:
	//! High Pass filter image.
	//
	//! High Pass filter an image by shifting a mask over the image.
	//! The mask: 	-1, -1, -1 
	//!			    -1,  8, -1
	//!				-1, -1, -1
	//! 
	//! /param image is the image that will be filtered.
	void filterImage(ImageRGB & image);
};

#endif