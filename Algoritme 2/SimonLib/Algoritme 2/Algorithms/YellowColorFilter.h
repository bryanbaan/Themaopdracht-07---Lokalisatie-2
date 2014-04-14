#ifndef YELLOWCOLORFILTER_H
#define YELLOWCOLORFILTER_H

#include <ImageRGB.h>

#include <math.h>

using namespace ImageLib;

//! YellowColorFilter class
//
//! This class is able to filter an image on the yellow color.
//!
//! Team: Localization
//! Author(s): Mitchell Werensteijn & Yusuf Syakur
//! Version: 1.0
class YellowColorFilter {
public:
	//! Filter an image on yellow.
	//
	//! Filter image on yellow.
	//! 
	//! /param image is the image that will be filtered.
	void filterImage(ImageRGB & image);

	// Function to convert a RGB value to HSV format.
	// Source: http://en.literateprograms.org/RGB_to_HSV_color_space_conversion_%28C%29
	static void RGB2HSV(float r, float g, float b, float & h, float & s, float & v);
};

#endif