#ifndef Threshold_H
#define Threshold_H
#include "Image.h"
#include "exectimer.h"
#include <iostream>

class Threshold {
private:
	BaseTimer* bt;
public:
	Threshold();
	~Threshold();
	void CreateThresholdImage(Image &sourceImage, Image &destinationImage);
};

#endif

