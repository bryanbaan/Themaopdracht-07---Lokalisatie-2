#ifndef LICENSELOCALIZER_H
#define LICENSELOCALIZER_H

#include <ImageLib.h>
#include "LicensePosition.h"
#include <vector>

using namespace ImageLib;

//! LicenseLocalizer class.
//
//! This class is able to find a license plate in a image.
//!
//! Team: Localization
//! Author(s): Mitchell Werensteijn & Yusuf Syakur
//! Version: 1.0
class LicenseLocalizer {
public:
	//! Find the license plate position.
	//
	//! /param image, the image in which a license plate will be searched.
	LicensePosition getLicensePlatePosition(ImageRGB & image);
};

#endif;