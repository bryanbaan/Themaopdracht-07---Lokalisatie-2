#ifndef INTENSITYHISTOGRAM_H
#define INTENSITYHISTOGRAM_H

#include <ImageLib.h>
#include "../LicensePosition.h"

#define MAXIMUMMINVALUE 30

using namespace ImageLib;

class IntensityHistogram {
public:
	LicensePosition getLicensePosition(ImageRGB & image, bool generateCSV = false);

private:
	void findPeakRange(int &leftSide, int &rightSide, int * values, int histogramSize);
	void saveToCSV(std::string filename, int * histogram, int arraySize);
};

#endif