#ifndef Histogram_H
#define Histogram_H
#include "Image.h"
#include "exectimer.h"
#include <iostream>
#include <fstream>

class Histogram{
private:
	BaseTimer* bt;
	std::string outputLocation = "../Histogrammen/";
public:
	Histogram();
	~Histogram();
	void CreateNormalizedHistogramCOLOR(Image &sourceImage, int binnr);
	void CreateNormalizedHistogramGRAY(Image &sourceImage, int binnr);
};

#endif