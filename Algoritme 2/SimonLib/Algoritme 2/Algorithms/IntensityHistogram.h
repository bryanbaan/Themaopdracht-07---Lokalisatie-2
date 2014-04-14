#ifndef INTENSITYHISTOGRAM_H
#define INTENSITYHISTOGRAM_H

#include <ImageLib.h>
#include "../LicensePosition.h"

#define MAXIMUMMINVALUE 30

using namespace ImageLib;

//! IntensityHistogram class
//
//! This class is able to find the position of the license plate
//! by searching for a peak in a histogram.
//!
//! Team: Localization
//! Author(s): Mitchell Werensteijn & Yusuf Syakur
//! Version: 1.0
class IntensityHistogram {
public:
	//! Get the license position.
	//
	//! Find the position of the license plate in a yellow filtered image
	//! by searching for a peak in a histogram.
	//! 
	//! /param image is the image in which the license plate has to be found
	//! /param generateCSV determines if the histograms have to be saved.
	LicensePosition getLicensePosition(ImageRGB & image, bool generateCSV = false);

private:
	//! Find the peak in a histogram.
	//
	//! /param leftSide is the left side of the peak which will be found.
	//! /param rightSide is the right side of the peak which will be found.
	//! /param values is the histogram.
	//! /param histogramSize is the histogram size.
	void findPeakRange(int &leftSide, int &rightSide, int * values, int histogramSize);

	//! Save histogram to file.
	//
	//! /param filename is the name of the file.
	//! /param histogram is the array which holds the values.
	//! /param arraySize is the size of the array.
	void saveToCSV(std::string filename, int * histogram, int arraySize);
};

#endif