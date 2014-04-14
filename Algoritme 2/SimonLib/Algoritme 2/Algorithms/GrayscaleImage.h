#ifndef GRAYSCALEIMAGE_H 
#define GRAYSCALEIMAGE_H

#include <ImageLib.h>

using namespace ImageLib;

//! GrayscaleImage class
//
//! This class is able to convert an image to grayscale.
//!
//! Team: Localization
//! Author(s): Mitchell Werensteijn & Yusuf Syakur
//! Version: 1.0
class GrayscaleImage {
public:
	//! Convert image to grayscale.
	//
	//! This function will convert a ImageRGB object to a ImageGray object.
	//! The class uses the NTSC standard method to convert the image to grayscale.
	//! Gray = 0.299 * Red + 0.587 * Green + 0.114 * Blue. 
	//!
	//! /param image is the image that will be grayscaled.
	//! /return ImageGray, the grayscaled image.
	ImageGray convertToGrayscale(ImageRGB & image);
};

#endif